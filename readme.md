# What would I like on my Public Release

## Testimonials like this would be great

In some amazing YouTube channel:

> Easier to use and navigate than ChiCAD. I feel like I wasted time dealing with those bugs and learning all
> those shortcuts.

From a YouTube channel sponsored by another EDA:

> It's feels more responsive than HardEDA - and it's written in Java! Can you believe it?

In a specific blog featuring all sort of "tutorials" in different EDAs:

> We are doing this only because this tools deserves it. But you certainly don't need a tutorial to work with it.

From a guy learning how to use EDA:

> It's amazing how I can follow tutorials on YouTube from guys using Linux, and I can do the exact same thing
> on my Mac.

# Expected Questions (and their answers)

* **Why another EDA?**
  Existing tools are very mature, but to a point they are getting old and hard to maintain. The big players
  are already consolidated in their areas, which makes it harder to release ground-shaking features. Meanwhile,
  the new players has strong focus on shiny features (like breadboard design or integration with PCB manufacturers),
  while forgetting the essentials.

* **Why "Brot"?**
  Because I was learning German, and that was the "word of the day". It means "bread" and it seems easy to speak
  in other languages - also, searching by "brot" resulted in no uses other than "bread in German", so it felt
  like a good name anyway.

* **What's the license?**
  GPLv3, with parts licensed with Apache License
* **Does it mean my designs must be open-source?**
  No. Think of it like "Libre Office" - if you create a spreadsheet with it, it does not need to be "open".

* **Why a Desktop app?**
  Designing in a web browser is cool, but it's limited. Key bindings may have funky response, specially in
  different platforms. Using native features may be browser-dependent. And there's always that rainy day when
  your Internet provider fails on you and you are blocked from playing around with your projects.

* **Why Java?**
  Because NetBeans is written in Java.
* **Then, why NetBeans?**
  It's an amazing platform, with a solid support for projects and visual editor. I have experience in NetBeans
  since it was owned by Sun (even before Oracle or Apache owned it). It's faster to add features, keeping the
  focus in what matter, like the diagram editors.
* **Do I need to learn Java?**
  No

* **Why XML?**
  XML is a horrible format if a human needs to maintain it, but it's an amazing format for machine processing.
  Also, NetBeans has a great support for XML, which saves time from developing and maintaining parsers and such.
* **Do I need to edit those XMLs?**
  A power-user may find it useful, but the average guy/gal will never need it.

* **Is it floating-point error-proof?**
  Yes. All coordinates are manipulated in a form of floating point without rounding errors. In a nutshell,
  instead of doing math as "number multiplied by a power of two" (the "classic" floating point), it does as
  "number multiplied by a power of ten" (more like what we do in real life).

* **Can I import my stuff from other EDAs?**
  If the licensing of the tool (and its file formats) allows it, then the answer is "eventually, yes". Otherwise
  the answer is "probably, no"
* **Can I export my stuff to other EDAs?**
  No, but this may be reconsidered in the future.

* **Can I export to Gerber?**
  Eventually, yes.
* **Is there support for buying PCBs?**
  No. The only option for you is export to Gerber and find a provider that suits your needs.

* **Can I store my project in a cloud service?**
  Eventually, yes.

* **Can I have a shared library of materials?**
  Eventually, yes.

* **What's the general workflow for a design?**
  You create a new project, import the required materials, design the circuit, then the PCB.
* **Why do I need a project?**
  To keep everything tied up. The project encapsulates everything related to a given design. Given a project folder,
  you can add it to a version control system (ex: GIT), or ZIP it and share it with others.
* **Why I need to import materials before using them?**
  This keeps your BOM (Billing of Materials) under control. This is quite important when sharing your project to
  others or when requesting quotes from external manufacturers. At first, it may look cumbersome, but as you advance
  in your project, they will tend to reuse the same materials.
* **Why do I need to draw my own materials? Why can't you provide a complete library of components?**
  Because the focus of the tools is to be easy to draw new materials. If you need only one minute drawing your own
  resistor, it means you won't need to invest one minute searching for the perfect combination of schema+PCB designs
  that fits whatever resistors you got in your toolbox in real life. Getting used to draw your own materials enables
  you to use any random component you bought on-line. This also avoids an "official library" focused on a specific
  niche (ex: Arduino shields v. THT v. SMT, etc) or in datasheets from a specific supplier.

# Expected Questions not Important to the Average User

* **Why the base Java package is "org.brot" if you don't own "brot.org"?**
  "brot.org" is about bread and this Java convention for reverse DNS name is horrible. If you want to rebrand
  your project or move it to a different host, you would need to do a massive refactoring to reflect that.

* **Is software fixed-point slower than hardware float-point?**
  Technically, yes. That's why algorithms using it needs to be as simple as necessary. This way, the speed
  difference is not an issue.