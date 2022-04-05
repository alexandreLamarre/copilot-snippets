package main

import "net/http"

// return an index.html file to the browser
func serveIndex(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "index.html")
}

// Start a webserver on localhost:8080
func serve() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("Hello World!"))
	})
	// Create an api endpoint /api/v1/hello
	http.HandleFunc("/api/v1/hello", func(w http.ResponseWriter, r *http.Request) {
		serveIndex(w, r)
	})
	http.ListenAndServe(":8080", nil)
}

func main() {
	serve()
}
