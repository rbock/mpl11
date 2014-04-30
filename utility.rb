##############################################################################
# Extensions
##############################################################################
require 'pathname'


class File
  def self.remove_ext(path)
    path.chomp(extname(path))
  end

  def self.sub_ext(path, ext)
    Pathname.new(path).sub_ext(ext).to_path
  end
end

class String
  def quote(char = '"')
    char + self + char
  end
end

module Enumerable
  def foldr(state, &block)
    reverse.inject(state) { |state, x| block.call(x, state) }
  end

  alias_method(:foldl, :inject)
end


class Numeric
  # round_up: Numeric -> Numeric
  #
  # Round up the integer to a given precision in decimal digits (default 0
  # digits). This is similar to `round`, except that rounding is always done
  # upwards.
  def round_up(ndigits = 0)
    k = 10 ** ndigits
    if self % k == 0
      self
    else
      (1 + self/k) * k
    end
  end
end


##############################################################################
# Utilities
##############################################################################
require 'delegate'
require 'erb'
require 'gnuplot'
require 'ruby-progressbar'
require 'timeout'


class Skip < Exception; end
class Done < Exception; end

# Yield to the block with each element of `xs`.
#
# Before starting, the block is invoked `rehearsals` times with the first
# element of `xs` (unless `xs` is empty).
#
# Gathering the dataset may be stopped by throwing `Done`. In this case,
# what has been gathered so far will be returned. Elements in the dataset
# can be skipped by throwing `Skip`.
def gather_dataset(xs, progressbar_title: 'Progress', rehearsals: 2)
  xs = xs.to_a
  progress = ProgressBar.create(format: "#{progressbar_title} %p%% | %B |",
                                total: xs.size)
  rehearsals.times { yield xs.first } unless xs.empty? # rehearse

  data = []
  catch Done do
    xs.each do |x|
      catch Skip do
        (y = yield x).tap { progress.increment }
        data << [x, y]
      end
    end
  end
  return data

ensure
  progress.finish
end

module MPL
  class Sequence < SimpleDelegator
    def headers
      self.class.headers(size)
    end
  end

  class Vector < Sequence
    def to_s
      initial, rest = map(&:to_s).take(50), map(&:to_s).drop(50)
      vectorN = "boost::mpl::vector#{initial.size}<#{initial.join(', ')}>"
      rest.reduce(vectorN) do |tail, x|
        "boost::mpl::v_item<#{x}, #{tail}, 0>" # we emulate mpl::push_back
      end
    end

    def self.headers(n)
      [
        "boost/mpl/vector/vector#{[n.round_up(1), 50].min}.hpp",
        n > 50 ? "boost/mpl/vector/aux_/item.hpp" : nil
      ].compact
    end
  end

  class List < Sequence
    def to_s
      init, tail = map(&:to_s)[0...-50], map(&:to_s).last(50)
      listN = "boost::mpl::list#{tail.size}<#{tail.join(', ')}>"
      init.zip(51..Float::INFINITY).foldr(listN) do |x_size, tail|
        x, size = x_size
        # we emulate mpl::push_front
        "boost::mpl::l_item<boost::mpl::long_<#{size}>, #{x}, #{tail}>"
      end
    end

    def self.headers(n)
      [
        "boost/mpl/list/list#{[n.round_up(1), 50].min}.hpp",
        n > 50 ? "boost/mpl/list/aux_/item.hpp" : nil
      ].compact
    end
  end
end


# Translate raise-based control flow to catch-based control flow.
#
# The block is executed and `throw_this` is thrown if the block raises any of
# the exception in the `rescue_this` array. If `rescue_this` is not an array,
# it is treated as an array of one element.
def on(rescue_this, throw_this)
  begin
    yield
  rescue *rescue_this
    throw throw_this
  end
end

def stop_after_consecutive(n, skip, stop)
  consecutive_skipped = 0
  -> (*args) {
    skipped = true
    result = catch skip do
      (yield *args).tap {
        consecutive_skipped = 0
        skipped = false
      }
    end

    if skipped
      consecutive_skipped += 1
      throw (consecutive_skipped >= n ? stop : skip), result
    else
      result
    end
  }
end

class Implementation
  @@implementations = Hash.new

  def self.list
    @@implementations.values
  end

  def self.[](id)
    if !@@implementations.has_key? id.to_sym
      raise ArgumentError, "unknown implementation #{id}"
    end
    @@implementations[id.to_sym]
  end

  def self.[]=(id, impl)
    if @@implementations.has_key? id.to_sym
      raise ArgumentError,
            "overwriting existing implementation #{id} with #{impl}"
    end
    @@implementations[id.to_sym] = impl
  end


  def initialize(id)
    @id = id.to_sym
    Implementation[@id] = self
    yield self if block_given?
  end

  attr_accessor :headers, :go
  attr_reader :id

  def includes(*args)
    [*headers.call(*args)].map { |hdr| "#include <#{hdr}>" }
  end
end

def plot(*rule_args)
  pattern, args, deps = Rake.application.resolve_args(rule_args)
  deps << proc { |name| (directory File.dirname(name)).name }

  rule(pattern, args => deps) do |rule|
    dataset_columns = -> (*indices) {
      rule.prerequisites.select(&File.method(:file?)).map do |file|
        Gnuplot::DataSet.new("\"#{file}\" using #{indices.join(':')}") do |ds|
          ds.with = "lines"
          _, ds.title = file.split('/', 2) # remove dataset/ part
        end
      end
    }

    Gnuplot.open do |io|
      Gnuplot::Plot.new(io) do |plot|
        plot.ylabel 'Compilation time'
        plot.format 'y "%f s"'
        plot.term   'png'
        plot.xrange '[0:300]'
        plot.output rule.name + '.time.png'
        plot.data = dataset_columns[1, 2]
        yield plot, :time if block_given?
      end
    end

    Gnuplot.open do |io|
      Gnuplot::Plot.new(io) do |plot|
        plot.ylabel 'Memory usage'
        plot.decimal "locale 'en_US.UTF-8'"
        plot.format 'y "%\'.0f kb"'
        plot.xrange '[0:300]'
        plot.term   'png'
        plot.output rule.name + '.memusg.png'
        plot.data = dataset_columns[1, 3]
        yield plot, :memusg if block_given?
      end
    end
  end
end

def dataset(xs, *rule_args)
  pattern, args, deps = Rake.application.resolve_args(rule_args)
  deps << proc { |name| (directory File.dirname(name)).name }

  rule(pattern, args => deps) do |ds|
    _, variant, cc, *_ = ds.name.split('/')

    compile = stop_after_consecutive(3, Skip, Done) do |*args|
      on([Skip, CompilationError], Skip) do
        Timeout::timeout(10, Skip) do
          code = yield ds, *args
          Compiler[cc].compile_code(code,
            include: ["~/code/mpl11/include", Dir.getwd])
        end
      end
    end

    stats = gather_dataset(xs, progressbar_title: ds.name, &compile)
    stats.map! { |x, stat| "#{x} #{stat.wall_time} #{stat.peak_memusg}" }
    IO.write(ds.name, stats.join("\n"))
  end
end

def quick_dataset(ds, xs)
  main = ERB.new(File.read("main.cpp"))
  main.filename = "main.cpp"

  dataset(xs, /dataset\/#{ds}/ => [
    proc { |name|
      header = File.sub_ext(File.basename(name), '.hpp')
      [File.file?(header) ? header : nil, 'main.cpp'].compact
    }
  ]) do |file, n|
    _, _, cc, strictness, impl = file.name.split('/')
    implementation = Implementation[impl]
    sequences = yield n
    main.result(binding)
  end
end