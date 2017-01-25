# SHA implementation

These are based directly upon the SHA methods as defined in
http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf

These are being written to get me back in to practice with C, and as
such are likely far from production quality.

## Guide to files
* `bit_manip`: bit mainpulation such as rotating bits in bytes and converting arrays to `uint64`.
* `sha`: Utility methods used by several types of SHA.
* `sha1`: Implementation of SHA-1
* `sha256`: Implementation of SHA-256
* `sha512`: Implementation of SHA-512

# License

Copyright 2015-2017 Daniel McAllaster. 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.




