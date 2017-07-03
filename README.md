# MangaSugestion
A software to recommand manga using Baka-update's list
Hello I've developed a little software for find a way to have a list of suggestion to find new manga.
The software is written in c. It's a prototype. I give you the sources and you have to use a compiler to build the executable. If you don't trust me, you can ask at someone who know to code. There no memory leak in my tests. Because it's only a prototype (and I'm lazy) manual adjustment have to be made by you.

There is 2 files :
- The code written in c who will be named here FileCode
- A text file who will be named FileData

FileData is composed of a list of [number of manga] [Personalid] [Manga1, Manga2 ...]

How that work : That find the N users closest to your lists (like when you click on “On 789 reading lists” in a manga's page) and will return the M manga the more in common manga in the  N users.

The FileData is based on public lists before July so if you did not not your list in public before July you have to wait another version or use computer scientist skills.

The first thing to do is to find your Personalid it's on your member page. My profile page it's https://www.mangaupdates.com/members.html?id=468919 so the Personalid is 468919. After in FileData you have to find the line with your Personalid (mine is 415 468919 70958 99920 … I've got  415 manga on my lists the  Personalid  468919 and manga n°70958 n°99920 … ) cut it then paste it on the first line.

Then you can change in FileCode : 
// Number of person close to you
 for the analyses  (here 50)
#define number 50

// Number of user analyzed (The maxi first user in the FileData, here 1000)
#define maxi 1000

// Number of manga suggested 
(here 100)
#define nbres 100

When you change FileCode you have to use the compiler again for change the executable.

