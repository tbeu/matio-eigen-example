from conan import ConanFile

class MatioEigenExampleConan(ConanFile):
    name = 'matio-eigen-example'
    version = '1.5.27'
    license = 'Unlicense'
    description = 'C++ example how to use the libraries matio and eigen via CMake and Conan.'
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeDeps'

    def requirements(self):
        self.requires('eigen/[>=3.4.0]')
        self.requires('matio/[>=1.5.27]')
