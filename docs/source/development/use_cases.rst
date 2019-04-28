Use Cases
=========

The following document includes the master list of use cases that we are considering handling so that we can rank them in our roadmap. If you have a new use case that is not included in this document, feel free to add it.

While this feels perhaps a bit unorthodox for an open source project, it is important that we take into consideration the many different users of the specification to allow for broad adoption.

System Actors and Stakeholder
-----------------------------

The following is a list of system actors and system stakeholders of CyanoByte.

Embedded Developers
~~~~~~~~~~~~~~~~~~~

It is expected that the primary users of the project are embedded developers. The CyanoByte specification creates a standardized format for datasheets so that the developer does not have to switch between many different formats. Additionally, it allows for code stubs to be created to more quickly develop firmware that uses a particular chip.

Key Competitive Advantages:

- Reduce the development time by automatically generating the non-application specific logic
- Make reading datasheets more efficient by creating a standardized format and interface
- More rapidly create proof-of-concepts using higher-level languages such as Python that can then be easily ported to embedded platforms

Peripheral Chip Manufacturer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order for the standard to become universally used, it is critical to get buy-in from manufacturers of electronic components. The CyanoByte specification can be used as both an internal tool during the development of a new peripheral that is formally defined and unambiguous as well as an external tool for developing datasheets and users guides. Additionally, by automatically generating example code in multiple programming languages for multiple platforms, the cost to create examples is greatly reduced.

Key Competitive Advantages:

- Reduce development time of code examples


Microcontroller Manufacter
~~~~~~~~~~~~~~~~~~~~~~~~~~

The CyanoByte generators may be used by, created by, or maintained by microcontroller manufacturers. If enough peripherals are available, then maintaining a CyanoByte generator for a particular microcontroller given the manufacturer a competitive advantage as it makes development on their platform far quicker and easier than others.


Electronics Hobbiest
~~~~~~~~~~~~~~~~~~~~

The electronics hobbyist market may be a key early user of the specification while it is under development.


Data Scientists and Machine Learning Engineers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The CyanoByte specifications provide a new source of data that was not previously accessible before.

Electronics Distributors
~~~~~~~~~~~~~~~~~~~~~~~~

The CyanoByte specifications provide a new source of information that can be used for novel parametric search tools. By using or creating specifications, distributors

Examples:

- DigiKey (https://www.digikey.com/)
- Arrow (https://www.arrow.com/)
- Mouser (https://www.mouser.com/)

Electronic Computer Aided Design Tools (ECAD)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Creators of ECAD tools can use the CyanoByte specifications to provide better hardware in the

Other Related Standards
~~~~~~~~~~~~~~~~~~~~~~~

The scope of CyanoByte is intentionally limited to only embedded communications at the logical level. It does not take into account anything related to the electrical signals. Therefore it is expected that the CyanoByte standard should work in conjunction with other standards that may already or eventually exist.


User Stories
------------

TODO