---
title: "User Journeys"
linkTitle: "User Journeys"
weight: 4
description: >
  What are some expected development flows?
---

Defining Critical User Journeys (CUJs) will allow the development of this project
to align with goals and expectations of the project consumers so that we can rank them in our roadmap.

If you have a new use case that is not included in this document, feel free to add it.

While this feels perhaps a bit unorthodox for an open source project, it is important that we take into
consideration the many different users of the specification to allow for broad adoption.

## Embedded Software Engineer
It is expected that the primary users of the project are embedded developers.
The CyanoByte specification creates a standardized format for datasheets so that the
developer does not have to switch between many different formats. Additionally, it allows
for code stubs to be created to more quickly develop firmware that uses a particular chip.

Additionally, simple errors could be mitigated by having a standardized specification that
requires no explicit work to get the library in the platform of choice.

**Key Competitive Advantages:**

* Reduce the development time by automatically generating the non-application specific logic
* Make reading datasheets more efficient by creating a standardized format and interface
* More rapidly create proof-of-concepts using higher-level languages such as Python that can then be easily ported to embedded platforms

## Sensor Hardware Manufacturer
I am a customer support engineer at a sensor chip manufacturer. In the past my role has been to assist
customers who buy our chips over email or phone. Support is called when the customer has difficulty
integrating a chip into their product. I'm told that "it doesn't work", and that starts weeks of intense
debugging with logic analyzers and trying to read code in all kinds of formats and platforms just to
find one typo.

I decided to create a Cyanobyte specification file for one of our chips and made it available as a
download on our store's website. The number of support queries has been reduced, and customers are
now more pleased. This seems to have led to an increase in customer satisfaction and retention.

In order for the standard to become universally used, it is critical to get buy-in from manufacturers of
electronic components. The CyanoByte specification can be used as both an internal tool during the
development of a new peripheral that is formally defined and unambiguous as well as an external tool
for developing datasheets and users guides. Additionally, by automatically generating example code in
multiple programming languages for multiple platforms, the cost to create examples is greatly reduced.

**Key Competitive Advantages:**

* Reduce development time of code examples

## Electronics Distributors
The CyanoByte specifications provide a new source of information that can be used for novel
parametric search tools.

**Examples:**

* DigiKey (https://www.digikey.com/)
* Arrow (https://www.arrow.com/)
* Mouser (https://www.mouser.com/)

## Oceanography
I am a researcher in Florida who is developing and deploying remotely operated vehicles (ROVs) in
the state's waterways to observe local wildlife and collect data related to water quality. This
requires sensors that can perform these measurements, work with output peripherals, and run on a
microcontroller with specific specifications to accomplish my team's goals.

This microcontroller may be selected due to cost, power consumption, peripheral support, environmental
impact, and other factors. As such, the selection may not be a common platform (ie. Raspberry Pi or
Arduino). When it comes time to build the software for the microcontroller, I may need to write
sensor and peripheral drivers from scratch.

As my research may come from a grant, limiting funding for a large development team, and the research
may need to be in a small timeframe, I want the ability to get started without a lot of software
overhead.

When I purchase these special sensors for my device, I make sure to download the Cyanobyte spec files
that are available on the manufacturer's site.

When searching for microcontrollers, support for Cyanobyte through a device template is a key factor,
as that means no time or effort will be required to support a particular sensor on my particular 
platform.

## Space Satellites
I am an engineer at a public or private space organization. We are developing a new satellite that will
be deployed into orbit. As the device will be expected to be in orbit for decades, under intense
conditions, we cannot use common off-the-shelf components. Additionally, given the cost of the satellite
and engineering time, a fatal error in the computer could bring the satellite down and destroy years
of effort.

Hardware manufacturers that may build space-ready peripherals, will also supply the engineering team
with Cyanobyte specification files. As the file comes directly from the manufacturer's hardware team,
there is a higher degree of reliability. Additionally, any errors can be corrected by publishing a new
file without any effort from the engineering team to mirror changes.

The microcontroller we're using is very specific to our use case, and doesn't have wide software
support. However, by maintaining our own Cyanobyte template instead of dozens of separate drivers, we
have reduced engineering cost and are able to focus more on polishing the remainder of the codebase.

## Hardware Startup
I am the technical lead for a small hardware startup which is selling to consumers. Based on our product
portfolio, we support a series of different microcontroller families with a custom operating system
developed in-house. We also have to support a series of drivers written on top of that operating system.

As our startup is small, we can't afford to hire more engineers even though we're facing a lot of
technical debt. After learning about Cyanobyte, we write a single template for our operating system
and import peripheral files from the manufacturers. This reduces engineering burden, and we can
refocus on building and marketing new products

## New IoT Platform
I am the product manager of a new IoT platform. We launched our first product several months ago but
have not been seeing a lot of traction. A big piece of criticism is a lack of software support. Our
platform doesn't have many drivers for common peripherals, which prevents a lot of adoption, which
prevents a growing community from writing drivers.

To resolve the chicken & egg problem, we build and release a Cyanobyte template file for our platform.
Suddenly, we are able to support a growing set of sensors and other peripherals without having to take
on the maintenance burden. As our platform may have some unusual idiosyncracies, providing an
off-the-shelf template file allows for high-quality drivers and code to be generated.

The CyanoByte generators may be used by, created by, or maintained by microcontroller manufacturers.
If enough peripherals are available, then maintaining a CyanoByte generator for a particular
microcontroller given the manufacturer a competitive advantage as it makes development on their
platform far quicker and easier than others.

## Student Project
I am a student at a school that specializes in engineering. My background is primarily in computer
engineering, although I have some experience in the C programming language. I am working on an embedded
hardware final project. Despite long hours and late nights, my microcontroller is not sending the right
data to the peripheral. The project is due in five hours.

I do an online search and find a Cyanobyte specification file for the peripheral. I also find an open
source project which is a Cyanobyte template file for the microcontroller I'm using.

After setting up the codegen tool and generating a driver, I import it into my project and it now works
in just a few minutes. Now I have time to write the accompanying report.

## Electronics Hobbyist

The electronics hobbyist market may be a key early user of the specification while it is under development.

## Data Scientists and Machine Learning Engineers

The CyanoByte specifications provide a new source of data that was not previously accessible before.

## Electronic Computer Aided Design Tools (ECAD)

Creators of ECAD tools can use the CyanoByte specifications to provide better hardware definitions. At
the moment, the electronic part values are not defined, but this could be a good extension to consider
in the future.

## Other Related Standards

The scope of CyanoByte is intentionally limited to only embedded communications at the logical level.
It does not take into account anything related to the electrical signals.

Therefore it is expected that the CyanoByte standard should work in conjunction with other standards
that may already or eventually exist.