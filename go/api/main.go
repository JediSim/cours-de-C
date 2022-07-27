package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"workspace/src/typeApi"

	"github.com/gorilla/mux"
)

var Articles []typeApi.Article

func homePage(w http.ResponseWriter, r *http.Request){
    fmt.Fprintf(w, "Welcome to the HomePage!")
    fmt.Println("Endpoint Hit: homePage")
}

func returnAllArticles(w http.ResponseWriter, r *http.Request){
	fmt.Println("Endpoint Hit: returnAllArticles")
	json.NewEncoder(w).Encode(Articles)
}

func returnSingleArticle(w http.ResponseWriter, r *http.Request) {
    vars := mux.Vars(r)
    key := vars["id"]

    // Loop over all of our Articles
    // if the article.Id equals the key we pass in
    // return the article encoded as JSON
    for _, article := range Articles {
        if article.Id == key {
            json.NewEncoder(w).Encode(article)
        }
    }
}


func handleRequests() {
    // creates a new instance of a mux router
    myRouter := mux.NewRouter().StrictSlash(true)
    // replace http.HandleFunc with myRouter.HandleFunc
    myRouter.HandleFunc("/", homePage)
    myRouter.HandleFunc("/all", returnAllArticles)
	myRouter.HandleFunc("/article/{id}", returnSingleArticle)
    // finally, instead of passing in nil, we want
    // to pass in our newly created router as the second
    // argument
    log.Fatal(http.ListenAndServe(":8080", myRouter))
}

func init() {
	Articles = []typeApi.Article{
        typeApi.Article{Id: "1", Title: "Hello", Desc: "Article Description", Content: "Article Content"},
        typeApi.Article{Id: "2", Title: "Hello 2", Desc: "Article Description", Content: "Article Content"},
    }
}

func main() {
	fmt.Printf("Articles: %v\n", Articles)
    handleRequests()
}
