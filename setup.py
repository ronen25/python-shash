from distutils.core import setup, Extension

def main():
    mod = Extension(
        'shash',
        sources = [ 'src/pyshash.c', 'src/simi.c', 'src/simiw.c', 'src/lookup3.c' ],
        extra_compile_args = [ '-march=native',  '-mtune=native' ,'-g0' ,'-std=c99' ]
    )

    setup(name="shash",
          version="1.0.0",
          description="Viliam Holub's shash, implemented as a Python module",
          author="Ronen Lapushner",
          author_email="ronenk17@gmail.com",
          url="https://github.com/ronen25/python-shash",
          ext_modules=[mod])

if __name__ == "__main__":
    main()
