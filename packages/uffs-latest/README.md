# UFFS

UFFS: Ultra-low-cost Flash File System

Project: http://uffs.sf.net/
Blog:    http://all-about-uffs.blogspot.com/
Q/A:     http://groups.google.com/group/uffs/

Author: Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

INTRODUCTION
------------

UFFS is a nand flash file system designed for embedded system.

UFFS have some unique and advanced features:
  * Low cost: e.g. it needs only 41K bytes RAM for 64MB NAND flash (page size 2048).
    
  * Fast booting: it reads only a few spares from each block, typically
    mounting a fully filled file system (Gbits) within one second.
    
  * Superb Reliability: 
    - The file system is designed for the embedded system which may 
        frequently lost power/reset without care.
    - Journal file system, the file system will automatically rollback
        to the last state when lost power on the middle of flash programing.
    - When 'write' return without error, the data is guarenteed been
        saved on flash.

  * Fast file create/read/write/seek.  
  * Bad-block tolerant, ECC enable and good ware-leveling.
  * There is no garbage collection needed for UFFS.
  * Support multiple NAND flash class in one system.
  * Support bare flash hardware, no operating system needed. 
  * Support static memory allocation (works without 'malloc').
  * Fully simulated on PC (Windows/Linux) platform.

Disadvantage:
  * space inefficency for small files: UFFS use at least one
   'block'(the minial erase unit for NAND flash, e.g. 16K ) for a file.
  * maximum supported blocks: 2^16 = 65535

Memory consuming example:
    For page size = 512:
        [VARY]Tree nodes: 16 * total_blocks 
        [CONST]Page Bufs: MAX_CACHED_BUFFERS(10) * (40 + pageSize(512)) = 5.4K 
        [CONST]Block Info caches: (24 + 14 * pages_per_block (32)) * MAX_CACHED_BLOCK_INFO (10) = 4.6K

        Example 1: 128M bytes NAND, 8192 blocks, total memory cost:
            (16 * 8192)128K + 5.4K + 4.6K = 138K bytes.
		
        Example 2: 32M Bytes NAND, 2048 blocks, total memory cost:
            (16 * 2048)32K + 5.4K + 4.6K = 42K bytes.
		
        Example 3: 16M bytes NAND, 1024 blocks, total memory cost:
            (16 * 1024)16K + 5.4K + 4.6K = 26K bytes.

    For page size = 2048:
        [VARY]Tree nodes: 16 * total_blocks 
        [CONST]Page Bufs: MAX_CACHED_BUFFERS(10) * (40 + pageSize(2048)) = 20.4K 
        [CONST]Block Info caches: (24 + 14 * pages_per_block (32)) * MAX_CACHED_BLOCK_INFO (10) = 4.6K

        Example 1: 512M bytes NAND, 8192 blocks, total memory cost:
            (16 * 8192)128K + 20.4K + 4.6K = 153K bytes.
		
        Example 2: 128M Bytes NAND, 2048 blocks, total memory cost:
            (16 * 2048)32K + 20.4K + 4.6K = 57K bytes.
		
        Example 3: 64M bytes NAND, 1024 blocks, total memory cost:
            (16 * 1024)16K + 20.4K + 4.6K = 41K bytes.
            

BUILD SIMULATOR REQUIREMENT
---------------------------
From V1.2.0, build uffs simulator requires 'cmake'.
'cmake' can be downloaded from: http://www.cmake.org/

or, under Debian/Ubuntu:
  sudo apt-get install cmake

BUILD SIMULATOR ON LINUX
------------------------
1) create a 'build' dir:

mkdir -p ~/build/uffs

2) create Makefiles and build:
  cd ~/build/uffs
  cmake <path_to_uffs>
  make

5) run simulator (interactive mode):
  src/utils/mkuffs
 
 
BUILD SIMULATOR ON WINDOWS
--------------------------

1) create a 'build' dir along with uffs source dir,
 d:\build\uffs

2) Create VC project files:
  cd build\uffs
  cmake <path_to_uffs>

3) Open uffs.dsw (or uffs.sln for VC > 6 ), compile & run.

 
LATEST SOURCE CODE
------------------
You can get the latest source code from git repository:
  git clone git://uffs.git.sourceforge.net/gitroot/uffs/uffs


CURRENT STATUS
--------------
UFFS 0.1.x is a working version on PC simulator, also has been ported to 
uBase embedded OS as a 'real world' product for thousands of copies,
it works fine so far.

UFFS 0.2.0 implementes full directory.

UFFS 1.0.0 is the first stable release at sf.net.

UFFS 1.1.0: support NAND flash with large page size (up to 2K).

UFFS 1.1.1: bug fixes. a tool for making uffs disk image.

UFFS 1.1.2: bug fixes. add more Flash Class. change Licence from GNU GPLv2 to GNU LGPLv2

UFFS 1.2.0: 
  - eliminate 'current path' and relatives. Now you should use absolute path in all
    uffs APIs. For dir, the fullname should end with '/'.
  - allow using static memory allocation, 'malloc' is no longer needed.
  - using cmake for building simulator.
  - bug fixes & minor changes.

UFFS 1.2.1:
  - improve bad block management
  - bug fixes
  - change Licence to modified GNU GPLv2.

UFFS 1.3.0:
  - improved flash interface
  - support hardware ECC
  - support user defined spare layout (for customized NAND flash controller)
  - support 4K page size
  - no partial page program required, support MLC NAND flash
  - reduced buffer flushes by grouping buffers
  - structual improvments and bug fixes
  
UFFS v1.3.1:
  - Tidy up three memory allocators: static, native and system.
  - Fix bugs in flash interface example.
  - Fix memory allocation bugs when using static memory allocator.
  - Add flash driver interface 'WriteFullPage()'.
  - Fix compilation errors for BlackFin DSP compiler.

UFFS v1.3.2:
  - Add POSIX like file system APIs.
  - Bug fixes.
  
UFFS v1.3.3:
  - Change Flash Interface, simplify interface.
  - Improved bad block handling.
  - Better support for MLC NAND flash.
  - Added hardware ECC and RS-ECC controller emulator.
  - Bug fixes.

UFFS v1.3.4
  - New UO_NOECC option for skipping ECC (fast reading).
  - POSIX compliance uffs_seek().
  - Improved unclean page detection (add new 'seal' byte in spare area).
  - Optional page data CRC.
  - Bug fixes.
  - Other improvements.
  
LICENCE
-------
  From v1.2.1, UFFS is released under a modified GNU GPLv2. (the same as eCos Licence)
  The full licence text can be found in the header of source files:
  
	  UFFS is free software; you can redistribute it and/or modify it under
	  the GNU Library General Public License as published by the Free Software 
	  Foundation; either version 2 of the License, or (at your option) any
	  later version.

	  UFFS is distributed in the hope that it will be useful, but WITHOUT
	  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	  or GNU Library General Public License, as applicable, for more details.
	 
	  You should have received a copy of the GNU General Public License
	  and GNU Library General Public License along with UFFS; if not, write
	  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
	  Boston, MA  02110-1301, USA.

	  As a special exception, if other files instantiate templates or use
	  macros or inline functions from this file, or you compile this file
	  and link it with other works to produce a work based on this file,
	  this file does not by itself cause the resulting work to be covered
	  by the GNU General Public License. However the source code for this
	  file must still be made available in accordance with section (3) of
	  the GNU General Public License v2.
	 
	  This exception does not invalidate any other reasons why a work based
	  on this file might be covered by the GNU General Public License.


TESTING UFFS WITH SQLITE3 REGRESSION TEST CASES
-----------------------------------------------
UFFS can be tested with sqlite3 regression test cases (on Linux).

1) install tcl8.5-dev on host PC:
	apt-get install tcl8.5 tcl8.5-dev

    # make sure your Linux is using tcl8.5 as the default tclsh:
		sudo update-alternatives --config tclsh
		(select "tclsh8.5" from the list.)

2) build uffs:
	mkdir -p ~/build/uffs
	cd ~/build/uffs
	cmake <path_to_uffs>

3) build sqlite3:
	cd <path_to_uffs>/src/test/sqlite3/sqlite-src-3070900
	./configure        					 # create some build support files
	git checkout -f Makefile config.h    # restore modified Makefile and config.h
	make test                            # start build 'testfixture' program.
	
	# now you'll see something like:
	Connect: Connection refused
	Assert (uffs_ret == ret && ret == bak_ret) fail at /home/.../src/test/api_test/os_uffs.c:os_unlink:329: unlink("/home/.../src/test/sqlite3/sqlite-src-3070900/./test.db-journal"), unix return 0, uffs return -1, bak return -1
	make: *** [test] Error 1

4) run test cases:
	Open two terminals.
	on termional A:
		cd ~/build/uffs
		src/utils/mkuffs -t 1024

		#on uffs simulator command line, enter:
		format /
		apisrv

	on terminal B:
		cd <path_to_uffs>/src/test/sqlite3/sqlite-src-3070900
		./test-uffs.sh

	Note: if you want to run mkuffs on another PC, for example, a Windows PC, you need to specify the IP address in test-uffs.sh.
	
	The test will take 1~4 hours, depends on how fast your Linux box is.


ACKNOWLEDGMENT
---------------
Special thanks for your contributions to:
(list in no particular order)

* Chen Jun <chj@nlscan.com>
* Michail <digiolog@mail.ru>
* Sjpu <sjpu@163.com>
* RobertGray <xennex@hotmail.com>
* Dongbo <dongbo@ftsafe.com>
* Cag <seucag@hotmail.com>
* Sergey <s_sazonov@m2m-t.ru>
* Chris Conrad <chris.conrad@halliburton.com>
* Vladimir <decoder@rambler.ru>
* Thien Pham <thienpham2008@yahoo.com>
* Emmanuel Blot <eblot.ml@gmail.com>
* Michael <yowong2@gmail.com>
* Mick D <mick-eng@sourceforge.net>
* Paul <paulr227@gmail.com>
* Rogerz <rogerz.zhang@gmail.com>


