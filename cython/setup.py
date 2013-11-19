from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize


exts = Extension(
    "face", ["face.pyx"], 
    libraries = ["faces"],
    library_dirs = ["release/"],
    depends=["cface.pxd"]
)

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [exts]
)
