fast-caesar-vigenere-cipher
===========================
An ANSI C, fast and efficient implementation of Caesar and Vigenère cipher.

## Compile
To compile please use run `$ ./compile.sh` instead of using the Makefile. 

This will create an executable called `fcvc` in the current directory.

## Help
```
Usage: fcvc {OPTION1} [OPTION2]
An ANSI C, fast and efficient implementation of Caesar and Vigenere cipher.

Only one or two options are permitted.
        fcvc {-a,-v} "INPUT STRING"
        fcvc -k KEY {-c,-d} "INPUT STRING"

        -a      Try all 26 alphabets for the INPUT STRING.
        -c      Encipher INPUT STRING.
        -d      Decipher INPUT STRING.
        -h      Print this help.
        -k      Use KEY to encipher or decipher INPUT STRING.
        -v      Decipher Vigenere INPUT STRING.

Exit value:
        0       no error occurred,
        != 0    some error occurred.

Report bugs to: franco.masotti@student.unife.it or franco.masotti@live.com
Full documentation at: <https://github.com/frnmst/fast-caesar-vigenere-cipher>
or available locally via: fcvc -h

fast-caesar-vigenere-cipher  Copyright © 2016  frnmst (Franco Masotti)
This program comes with ABSOLUTELY NO WARRANTY; for details see
'LICENSE' file or <https://www.gnu.org/licenses/gpl-3.0.en.html>
This is free software, and you are welcome to redistribute it
under certain conditions; see 'LICENSE' file or
<https://www.gnu.org/licenses/gpl-3.0.en.html> for details.
```

## Explanation
Since Vigenère's cipher is a general case of Caesar cipher they can be 
implemented in the same function.


# License
![https://www.gnu.org/graphics/gplv3-127x51.png](https://www.gnu.org/graphics/gplv3-127x51.png)

Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
<franco.masotti@student.unife.it>

fast-caesar-vigenere-cipher is free software: you can redistribute it and/or 
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

