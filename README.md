# python-shash
Charikar's Hash for Identifying Similar Documents

## What is it?
This module wraps around an excellent [C implementation](https://github.com/vilda/shash/) of [Charikar's Hash](https://en.wikipedia.org/wiki/Moses_Charikar), 
used to identify (and thus check) the similarity of documents.

It has been tested with Python 3.8 on Ubuntu 20.04 AMD64, but should work with pretty much every 3.x version of Python.

## Binary Installation
*There is none yet*, since I would like to thoroughly test this module in a production envrionment.
When that's done, it will be uploaded to PyPI.

## Compilation From Source
Clone the repository and build from source:
```bash
$ git clone https://github.com/ronen25/python-shash
$ cd python-shash
$ python3 setup.py install
```
It is recommended to do so in a virtual environment, so as not to pollute your global environment.

## The API
The API is rather simplistic and remains true to the original C source, with two hash functions
and a Hamming distance function.

To import the module, use:
```
import shash
```

| Function | Parameters | Description |
| -------- | ---------- | ----------- |
| `charikar_hash64`| `str` or `bytes` array | Calculates Charikar's hash for the given data |
| `charikar_hash64_wide`| `str` or `bytes` array **;** token width (`int`) | Calculates Charikar's hash for the given data, with configurable `token_width` |
| `hamming_dist` | Two integers, representing Charikar hashes | Calculates the Hamming distance between the two hashes |

## Example
```python
import shash
s1 = 'testing this beautiful string'
h1 = shash.charikar_hash64(s1)

print(h1)
>>> 8049384540012662773

s2 = 'testings this beautiful string'
h2 = shash.charikar_hash64(s2)

print(h2)
>>> 5115011339482989567

print(shash.hamming_dist(h1, h2))
>>> 17

print(shash.hamming_dist(h1, h1)) # Strings are similar, should print 0
>>> 0

s4 = 'testing this beautiful strings'
h3 = shash.charikar_hash64(s4)

print(shash.hamming_dist(h1, h3))
>>> 17
```

## License
This library is distributed under the [Creative Commons Attribution 3.0 Unported](http://creativecommons.org/licenses/by/3.0/) License.