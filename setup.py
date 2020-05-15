import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

with open("requirements.txt", "r") as fh:
    install_requires = [line.rstrip() for line in fh]

setuptools.setup(
    name="cyanobyte",
    version="0.0.1",
    author="Google Inc.",
    author_email="fleker@google.com",
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
    python_requires=">=3.0",
    install_requires=install_requires,
    entry_points={
        "console_scripts": [
            "cyanobyte-codegen=cyanobyte.codegen:gen",
            "cyanobyte-validator=cyanobyte.validator:click_valdiate"
        ],
    },
)
