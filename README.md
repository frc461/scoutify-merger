scoutify-merger
===

Scoutify-merger is the second part of the Scoutify software compilation.
This component is designed to handle all of the pre-generated data from each client, transferred [for now, at least] through physical means such as through the use of a USB "flash drive" or over FTP or some other way.
It is designed to be used after ALL of the data is generated, to then find a list of the best teams to ally with.

Usage
---

[more to come when arguments get parsed and we can generate a usage string from stuff]

API
---

Generally speaking, if you're editing raw values you're doing it wrong.
For example, you should never set values in the database by hand as records are updated when the right functions are called and setting values by hand does not call them.
Likewise, manually inserting arguments into the global argument stack is a bad idea as things can go very wrong.
If you need a function to do a specific purpose, you can ask for it or write it yourself, but don't just change values by hand.
It's generally a bad idea.

[documentation to come later]

License
=======
Copyright Christopher Cooper and Kristofer Rye 2013

scoutify-merger is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

scoutify-merger is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with scoutify-merger.  If not, see <http://www.gnu.org/licenses/>.
