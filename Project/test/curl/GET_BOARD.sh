PORT=$1
NAME=$2
curl -X GET "127.0.0.1:$PORT/board/$NAME"
