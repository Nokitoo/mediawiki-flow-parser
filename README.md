Mediawiki Flow Parser
=====================

Convert a Mediawiki Flow to a terminal flow. (Readable by bots or humans)
API_PATH is the directory path of API.

Installation instructions
-------------------------
<ol>
<li>Install the cURL library</li>
```shell
    $ cd API_PATH/curl
    $ ./configure
    $ make
    $ sudo make install
```
<li>Install the jansson library</li>
```shell
    $ cd API_PATH/jansson
    $ ./configure
    $ make
    $ sudo make install
```
<li>Start the API with the url of flow as parameter</li>
```shell
    $ cd API_PATH
    $ make
    $ ./flow_parser "http://url_of_flow/"
```
<li>Use of API</li>
```shell
   $ Type "exit" or press ^D to exit the API
```
</ol>
Other
-----

The mediawiki flow page: http://www.mediawiki.org/wiki/Flow
This project is under MIT License see `LICENSE` file for more details.
