Mediawiki Flow Parser
=====================

Convert a Mediawiki Flow to a terminal flow. (Readable by bots or humans)
API_PATH is the directory path of API.

Installation instructions
-------------------------

1.&nbsp;Install the cURL library

```shell
	$ cd API_PATH/curl
	$ ./configure
	$ make
	$ sudo make install
```
2.&nbsp;Install the jansson library
```shell
	$ cd API_PATH/jansson
	$ ./configure
	$ make
	$ sudo make install
```
3.&nbsp;Start the API
```shell
	$ cd API_PATH
	$ make
	$ ./flow_parser [-H]
```
	-H argument increase human readability.
4.&nbsp;Use of API
```shell
	$ Type "exit" or press ^D to exit the API
```

Other
-----

The mediawiki flow page: http://www.mediawiki.org/wiki/Flow
This project is under MIT License see `LICENSE` file for more details.
