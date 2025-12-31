# BookTracker

A mimimalist book tracking command line application.

## Installation

To install clone the repository and run:

```bash
make install
make tidy
```

This will install the binary in `/usr/local/bin/book`.

## Usage

BookTracker allows you to add, remove, and list books in your reading list. The database of books is stored in a txt in `$HOME/.book/`. To add a book run

```bash
book add "book title"
```

You will then be promped for an author name, a date started, what the status is (e.g. reading, read, to be read or did not finish), a completed date if you have read it and any notes. Every added book is assigned a unique ID which can be found by running 

```bash
book ls
```

This command will return a list of your books with their status and ID. You can see any notes associated with a book by running

```bash
book show <ID>
```

To delete a book run

```bash
book del <ID>
```

You can also modify a book by running

```bash
book mod <ID> <section> "New value"
```

where section can be any of "title", "author", "started", "completed", "status" and "notes".

You can see a plot of your reading history by running

```bash
book plot
```

and see the version of the program with

```bash
book version
```

There is a `help` function which can be accessed with

```bash
book help
```

but it currently isn't very helpful! The best thing to do is to refer to this README for help.

## Roadmap

A roadmap is probably a bit too grand a term for a small project like this but ultimately I would like to 

- add a stats command that shows users how many books they have on their tbr, how many they have read this year etc.
