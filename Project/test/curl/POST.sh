PORT=$1
curl -X POST "http://127.0.0.1:$PORT/boards/name"
curl -X POST "http://127.0.0.1:$PORT/boards/newname"
