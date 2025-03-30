REPO_NAME = chess_game
COMMIT_MSG = "commited"

all:
	echo "nicio problema"

update:
	git add .
	git commit -m "${COMMIT_MSG}"
	git push origin main

pull:	
	git pull origin main

status:
	git status

logs:
	git log --oneline

compile:
	gcc -Wall -o p main.c functions.c classic.c -lSDL2 -lSDL2_image -lSDL2_ttf

run:
	gcc -Wall -o p main.c functions.c classic.c -lSDL2 -lSDL2_image -lSDL2_ttf
	./p