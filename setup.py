import setuptools
from cyanobyte import __version__

with open("README.md", "r") as fh:
    long_description = fh.read()

with open("requirements.txt", "r") as fh:
    install_requires = [line.rstrip() for line in fh]

setuptools.setup(
    name="cyanobyte",
    version=__version__,
    author="Google Inc.",
    author_email="fleker+cyanobyte@google.com",
    description="A package that generates library files for a peripheral given an intermediary layer (YAML files)",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/google/cyanobyte",
    packages=setuptools.find_packages(exclude=("test",)),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.7",
    install_requires=install_requires,
    entry_points={
        "console_scripts": [
            "cyanobyte-codegen=cyanobyte.codegen:gen",
            "cyanobyte-validator=cyanobyte.validator:click_valdiate"
        ],
    },
    setup_requires=['setuptools_scm'],
    include_package_data = True,
)
