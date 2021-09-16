# What would I like on my Public Release

## Testimonials like this would be great

From a software engineer doing some hardware for fun:

> EDAs always intimidated me because I'm not a visual person. I love how I can
> describe my hardware and version it using GIT without dealing with weird
> merges.

From a YouTube channel sponsored by a PCB manufacturer with their own EDA

> It's feels more productive than HardEDA - their PCBs are great, but I will
> use Brot for my designs

In a specific blog featuring all sort of "tutorials" in different EDAs:

> We are doing this only because this tools deserves it. But you certainly
> don't need a tutorial to work with it.

From a guy learning how to use EDA:

> It's amazing how I can follow tutorials on YouTube from guys using Linux, and
> I can do the exact same thing on my Mac.

# Expected Questions (and their answers)

* **Why another EDA?**
  Existing tools are very mature, but to a point they are getting old and hard 
  to maintain. The big players are already consolidated in their areas, which 
  makes it harder to release ground-shaking features. Meanwhile, new players
  has strong focus on shiny features (like breadboard design or integration
  with PCB manufacturers).

* **Why "Brot"?**
  Because I was learning German, and that was the "word of the day". It means
  "bread" and it seems easy to speak in other languages - also, searching by
  "brot" resulted in no uses other than "bread in German", so it felt like a
  good name anyway.

* **What's the license?**
  MIT
* **Can I make money with my designs?**
  Yes, definitely. If you do so, please think about "giving something back" to
  the Brot community. It can be a tip, but bug reports, pull requests or
  "spreading the word" are gladly accepted as well.

* **Why a command-line toolkit?**
  Visual design with drag-and-drop is cool, but it does not feel right from a
  software developer perspective. EDAs are either monolithic and complex to
  learn or a frankenstein composed by parts that don't look like they belong
  to each other. In software development, composition is a key concept - just
  think how Lego pieces can be mounted together in ways that goes beyond what
  the original Lego designers thought about. The [Unix philosophy][unix-phi]
  is a powerful companion for this scenario: the output of a tool can be fed
  as the input of the next and new tools can be composed or introduced as
  intermediate steps without breaking the design.

* **Can I import my stuff from other EDAs?**
  No.
* **Can I export my stuff to other EDAs?**
  No.
* **It sounds like a vendor-lock. Is it a vendor-lock?**
  Not really. There are multiple tools in this market and there is no single
  standard among them. Any effort spent on migration is probably better spent
  at improving Brot itself. It is an easier transition if a new user starts a
  project from scratch instead of reversing engineering their own projects
  after a migration. It would be the same as migrating C++ source to Rust.
  
* **Can I export to Gerber?**
  Yes.
* **Is there support for buying PCBs?**
  No. The only option for you is export to Gerber and find a provider that
  suits your needs.

* **Can I version-control my project?**
  Yes. Your Brot project is textual and written by humans (mostly). It means a
  VCS like GIT is more than able to store your project.
* **Can I have a shared library of materials?**
  Yes. It behaves like shared code. As an example, if you use GIT, you can
  create a repository for your shared library then import it in your projects
  using submodules.

* **What's the general workflow for a design?**
  Describe your [BOM][bom] then a list of components and its connections. That
  is the bare minimum. After that, it depends on your objective: do you want to
  add a visual design to a blog/vlog? Run a DRC? Maybe order a PCB? Simulate
  the circuit? Different tools will require more data and yields different
  results.
* **Hold on... Can I do all of that (DRC, simulation, etc)?**
  Eventually, you will be able to.
* **Running multiple tools sounds slow. Is it slow?**
  Individual tools may be slow, but you can tweak your workflow to circumvent
  these issues - in the same way a software developer (normally) does not
  recompile the whole project when they change a single file.

* **Do I need to define my own components?**
  Yes. The focus is to be easy to draw new materials. If you only need a couple
  of minutes drawing your own resistor, you can save a lot of time searching
  for the perfect combination of schema+PCB designs that fits whatever
  resistors you got in your toolbox in real life. Getting used to draw your own
  materials enables you to use any random component you bought on-line. This
  also avoids an "official library" focused on a specific niche (ex: Arduino
  shields v. THT v. SMT, etc) or in datasheets from a specific supplier.

* **Metric or Imperial?**
  Both. You can also mix both thru the magic of suffixed literals.

* **Is it prone to floating-point errors?**
  No. All positions are described and processed as an integer number and a unit
  (or fraction of a unit, such as `3mm`, `10mil`, etc). It is mathematically
  more accurate to do `3mm + 100um` as `(3 * 10^3 + 100)um` than `3 + 0.1` and
  less prone to overflows than `3_000_000 + 100_000`.

* **Do I need to learn a programming language?**
  No.

* **Do I need to learn something else?**
  It might be useful to learn about some automation tools, like Make or shell
  scripting. But, if you can also use only Brot and do it all by yourself.

* **Are Brot tools turing-complete?**
  No. If you need to describe a project in a turing-complete way (i.e. using
  loops, variables, etc) then you are probably safer with a new tool that can
  generate Brot descriptors.

[bom]: https://en.wikipedia.org/wiki/Bill_of_materials
[unix-phi]: https://en.wikipedia.org/wiki/Unix_philosophy

# Expected questions from maintainers

* **Why C++?**
  C++ is a good compromise between strongly-typed, performance, wide adoption
  and easy to compose (both internally and as tools). Also, I like C++.

* **Why STL?**
  STL might not be the best, but it is there "for free".

* **Why no Boost/libray XYZ?**
  Because it does not come "for free". Each new dependency is a new source of
  issues. Boost may provide some value, but tools are meant to be as simple as
  possible - therefore fast to create and test.

* **Why CMake?**
  Mostly because it provides a cross-platform way of compiling the whole
  project, while allowing an easy-to-maintain composible interface.
