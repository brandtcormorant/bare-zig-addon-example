# bare-zig-addon-example

Zig for low-level control and performance & JavaScript via [Bare](https://github.com/holepunchto/bare) for the vibes. Glued together with C.

## Advantages of using Zig & Bare JS together

- Memory safety and great build tooling from Zig for low-level control in areas where performance, precision, and device access matter.
- The ubiquitousness and familiarity of JavaScript.
- Great learning opportunity for understanding FFI, type systems, and how different languages interact.
- Foundation for more complex native addons - once you have this pattern working you can build on it.

## Drawbacks of Zig integration with Bare

There's one annoying, hopefully temporary drawback:

- Hand-edited header files. Right now it's hard to generate C headers for code exported from Zig. That means we might have to create and edit header files by hand for now. Not a big deal unless your zig library is big.

Aside from that, if you've dealt multi-language projects before you'll recognize the other challenges:

- You need to coordinate two different build systems (Zig & CMake).
- Types and error handling differ between Zig, C, and JavaScript.
- When things go wrong, you need to debug across language boundaries, which can make it harder to track down issues.

## Zig for the future

If you'd rather just use C that is a good and lovely option.

But if you're working with existing Zig projects or building new ones and want to have JavaScript integration this is a really interesting option.

Using Zig's build system together with Bare's dev tools like [bare-make](https://github.com/holepunchto/bare-make) (a wrapper around cmake with Bare-specific tooling) is already really effective.

## Building

> This example addon is based on the [template repository](https://github.com/holepunchto/bare-addon) for creating Bare native addons. For information on how to use the template, see [Creating a repository from a template](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template).

This project requires Zig, Bare, and bare-make. Start by installing them:

### Install Zig

Download Zig from the [official downloads page](https://ziglang.org/download/). On macOS with Homebrew:

```console
brew install zig
```

### Install Bare & bare-make

[bare-make](https://github.com/holepunchto/bare-make) is used for compiling the native bindings. Install it globally:

```console
npm i -g bare bare-make
```

### Build Process

First, build the Zig library:

```console
zig build
```

Next, generate the build system for compiling the bindings, optionally setting the `--verbose flag to enable debug symbols and assertions:

```console
bare-make generate [--verbose]
```

This only has to be run once per repository checkout. When updating `bare-make` or your compiler toolchain it might also be necessary to regenerate the build system. To do so, run the command again with the `--no-cache` flag:

```console
bare-make generate [--verbose] --no-cache
```

With the Zig library built and build system generated, compile the bindings:

```console
bare-make build
```

This will compile the bindings and output the resulting shared library module to the `build/` directory. To install it into the `prebuilds/` directory where the Bare addon resolution algorithm expects to find it:

```console
bare-make install
```

For faster development iteration, the shared library module can be linked into the `prebuilds/` directory rather than copied using the `--link` flag:

```console
bare-make install --link
```

Note: Prior to publishing the module, ensure no links exist within the `prebuilds/` directory as these will not be included in the resulting package archive.

## Run the example

Finally, we can execute the JavaScript example.

```
bare example.js
```

The output should look like:

```
from bare c binding: n1, 1.000000
from bare c binding: n2, 1.000000
from zig library: n1: 1e0, n2: 1e0
from zig c api export: n1: 1e0 + n2 1e0 = 2e0
from bare c binding: sum 2.000000
from javascript: 2
```

![A gif of actor Boris Karloff out of character but still in the makeup and custome of Frankenstien's monster sticking out his tongue](./monster.gif)

It's a happy monster don't be mean to it 😅

## License

Apache-2.0
