# linkstatic doesn't seem to work in macOS Sierra

`foo.c` should fail to link (as `missing_function` is missing) but instead it fails
at runtime when compiled with Bazel:

    ~/bazel-playground$ bazel build ...
    INFO: Found 1 target...
    Target //:foo up-to-date:
      bazel-bin/foo
    INFO: Elapsed time: 3.957s, Critical Path: 0.22s
    ~/bazel-playground$ ./bazel-bin/foo
    Done!
    ~/bazel-playground$ ./bazel-bin/foo bar
    Attempting to call missing_function...
    dyld: lazy symbol binding failed: Symbol not found: _missing_function
      Referenced from: /Users/iain/bazel-playground/./bazel-bin/foo
      Expected in: flat namespace

    dyld: Symbol not found: _missing_function
      Referenced from: /Users/iain/bazel-playground/./bazel-bin/foo
      Expected in: flat namespace

    Abort trap: 6

The `cc_binary` rule has `linkstatic = 1` which is supposed to link a mostly-static
binary.

Simply compiling by hand with `clang` with the default options does the right thing:

    ~//bazel-playground$ clang foo.c -o foo
    Undefined symbols for architecture x86_64:
      "_missing_function", referenced from:
          _main in foo-f767bf.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
