REPO_NAME = chess_game
COMMIT_MSG = "committed"

all:

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

