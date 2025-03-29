REPO_NAME = chess_game
COMMIT_MSG = "comitted"

all:

update:
	git add main.c Makefile
	git commit -m "${COMMIT_MSG}"
	git push origin main

pull:
	git pull origin main

status:
	git status

logs:
	git log --oneline

compile:
	gcc -Wall -o p main.c -lSDL2 -lSDL2_image -lSDL2_ttf
