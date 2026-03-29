# Comics Tagger

**WORK IN PROGRESS**

Just a note on the current state of the project, I'm developing this in my
free time pretty much just for my collection of comics I've scanned into
CBZ files.

The program itself is more so a passion project where the quality and 
reliability of the code is paramount over speed of development.


## Description

Comics tagger is a program to add metadata to comics and manga that are in the
cbz format.

For the moment it uses the xml format to handle this.

**Features:**
- Opens `*.cbz` comic files for editing.
- Writes in xml format.
- Features CLI interface default.
- Multi-file selection, enables bulk editing of tags.


## Dependencies

- WX widgets
- libzip
- sqlite
- openmp?

## Modules

- `cbz.h`:: Compressed comic archive
- `cvectors.h`:: C Dynamic memory vectors implimentation.
- `result_returns.h`:: Gives more comperhensive return, error and return system.


## Roadmap

- [ ] Add searchable directories.
- [ ] Add code to find all cbz comics.
- [ ] Add or edit xml inside comics.
- [ ] Add Artist(s) prompt
- [ ] Add groups(s) prompt
- [ ] Add automatic metadata edit data tags.
- [ ] Add translator prompt.
- [ ] Add Published date prompt.
- [ ] Add number of pages auto add.
- [ ] Add Languages tags.
- [ ] Add Source URL prompt.
- [ ] Add automatic web search for matching comic.
- [ ] Create common tags database.
- [ ] setup automatic comic pop-up to browse comic during tagging.
- [ ] Add user rating out of 5.

## Crazy Future Features?

- [ ] AI content tagger/classifier.
- [ ] AI language translator.
- [ ] Re-Encoding / compression optimizer.
- [ ] Reverse image search.
- [ ] Automatic tag extractor(modular)
- [ ] User adjustable memory caching.
- [ ] Add multilanguage GUI support.

## Instructions

The build process is automated using the `otto.sh` shell script in the 
projects root directory.


```sh
chmod +x ./otto.sh
./otto.sh #Follow on-screen instructions.
```

## Q&A

**Q:** Doesn't a program already exist for this?
**A:** Yes, most of them use interpreted languages, lack OS support for things
like FreeBSD, MacOS and rely on dead/unavailble packages...also they are slow.

**Q:** Why are you using C?
**A:** It's portable and easy for almost anyone to read if they do any programming
at all. Also it makes dealing with system calls and such easy imho, no need to
spend all my time fighting bindings that don't quite work correctly.

**Q:** I found a problem with the program but I don't code, how can I help?
**A:** If you see somethign that you haven't already found under issues you can
make a new one to let me know.

**Q:** Why don't you write it in <your language here>?
**A:** Speed, compatability, portability. Also library support, becuase I'll 
probably hit the fetal position if I have to use rust FFI or some bindings
crate/package that will be abandoned in 0.05 Seconds after I've stated using it.

**Q:** Why hasn't my PR been accepted?
**A:** Likely the code, didn't pass or have tests, wasn't formatted correctly,
contains AI slop, or has and out of date fork.


