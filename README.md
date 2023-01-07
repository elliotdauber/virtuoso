# virtuoso

This is Virtuoso, a virtual machine I'm building in C++ to learn about VMs and good code design. Currently, there is only a simple interpreter/executor for the low-level language that you would compile to (called VCode) in order to run code on Virtuoso. Check out vcode.txt for an overview of the language.

I've created a compiler (the "virtualizer", or "vcompiler") for a very simple high level language. You can find it in the /virtualizer directory. Just run make in the directory and run ./vcompiler infile.vy outfile.vt to compiler an infile in the high-level language to the outfile, in VCode. Each program must have a function called "main".

I plan to add many more features, including a garbage collector, custom threading, and others. There is also still a lot to do for the interpreter, such as proper error handling and building out the language a bit. I've designed it so that the latter is incredibly easy to do.

There are a few sample programs in the /programs directory. Run make to build the Virtuoso binary, and then you can try it on .vt files uisng ./virtuoso <filename>
