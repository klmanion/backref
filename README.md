# backref
backref -- compress a file by replacing repeated characters with a back reference.

backref can preform and undo the operation on a string,
where redundant text is replaced by a back-reference to its prior occurence in the style of <p,n>,
where the position of the beginning of the pattern is indicated by an integer p,
which is how many indices prior to the last printing character the pattern starts,
and the length is an integer n.

For example, if the minimum length of a back-reference is set to 4, the following string:
`how␣much␣wood␣could␣a␣woodchuck␣chuck␣if␣a␣woodchuck␣could␣chuck␣wood`,
would be encoded as: `how␣much␣wood␣could␣a<12,5>chuck␣<5,6>if<20,14><38,5><11,6><21,4>`.
Because a back-reference can reference a back-reference,
the string: `xxxxx`, could be encoded as: `x<0,4>`.
## Installation
Run the following commands to automake and install backref and the man page:
```bash
./autogen.sh
make
make install
```
## History
The idea for backref comes from Berkeley's fall 2001 programming contest, problem \#2.
The desideratum here is altered,
and more aligned with the input an end-user would provide,
rather than expecting a contest-style input file.
