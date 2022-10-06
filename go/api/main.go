package main

import (
	"context"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"workspace/src/typeApi"

	"github.com/gorilla/mux"
	"github.com/joho/godotenv"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"

	"github.com/golang-jwt/jwt/v4"
)

var Articles []typeApi.Article
var ctx = context.TODO()
var collection *mongo.Collection
var jwtKey []byte

func homePage(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Welcome to the HomePage!")
	fmt.Println("Endpoint Hit: homePage")
}

func returnAllArticles(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Endpoint Hit: returnAllArticles")
	// json.NewEncoder(w).Encode(Articles)
	cur, err := collection.Find(ctx, bson.M{})
	if err != nil {
		json.NewEncoder(w).Encode(err)
		return
	}
	var results []typeApi.Article
	if err := cur.All(ctx, &results); err != nil {
		json.NewEncoder(w).Encode(err)
		return
	}
	json.NewEncoder(w).Encode(results)
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

func createNewArticle(w http.ResponseWriter, r *http.Request) {
	// get the body of our POST request
	// unmarshal this into a new Article struct
	// append this to our Articles array.
	reqBody, _ := ioutil.ReadAll(r.Body)
	var article typeApi.Article
	json.Unmarshal(reqBody, &article)
	// update our global Articles array to include
	// our new Article
	fmt.Println(article)
	var findArticle bson.M
	err := collection.FindOne(ctx, bson.M{"id": article.Id}).Decode(&findArticle)

	if err == mongo.ErrNoDocuments {
		_, err = collection.InsertOne(ctx, article)
		if err != nil {
			json.NewEncoder(w).Encode(err)
			return
		} else {
			json.NewEncoder(w).Encode(article)
			return
		}
	}

	if err != nil {
		json.NewEncoder(w).Encode(err)

	} else {
		json.NewEncoder(w).Encode("Article already exists")
	}

}

func deleteArticle(w http.ResponseWriter, r *http.Request) {
	// once again, we will need to parse the path parameters
	vars := mux.Vars(r)
	// we will need to extract the `id` of the article we
	// wish to delete
	id := vars["id"]

	// we then need to loop through all our articles
	for index, article := range Articles {
		// if our id path parameter matches one of our
		// articles
		if article.Id == id {
			// updates our Articles array to remove the
			// article
			Articles = append(Articles[:index], Articles[index+1:]...)
		}
	}

}

func updateArticle(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id := vars["id"]
	// si on se réfère pas au meme type la caste des champs est prise en compte
	var updatedEvent typeApi.Article
	reqBody, _ := ioutil.ReadAll(r.Body)
	json.Unmarshal(reqBody, &updatedEvent)
	updatedEvent.Id = id
	// var update bson.M
	// for key, value := range updatedEvent {
	// 	update[key] = value
	// }
	fmt.Println(bson.M{"$set": updatedEvent})
	err := collection.FindOneAndUpdate(ctx, bson.M{"id": id}, bson.M{"$set": updatedEvent}).Decode(&updatedEvent)
	if err != nil {
		if err == mongo.ErrNoDocuments {
			json.NewEncoder(w).Encode("Article not found")
		} else {
			json.NewEncoder(w).Encode(err)
		}
	} else {
		json.NewEncoder(w).Encode(updatedEvent)
	}

}

func createToken(w http.ResponseWriter, r *http.Request) {

	reqBody, _ := ioutil.ReadAll(r.Body)
	var user jwt.MapClaims
	json.Unmarshal(reqBody, &user)

	var key interface{}
	key, err := jwt.ParseRSAPrivateKeyFromPEM(jwtKey)
	if err != nil {
		fmt.Println(err)
		json.NewEncoder(w).Encode(err)
		return
	}
	// key = interface{}(jwtKey)
	fmt.Println("key :", key)

	alg := jwt.GetSigningMethod("EdDSA")

	if alg == nil {
		fmt.Println("Invalid signing method")
		return
	}

	token := jwt.NewWithClaims(alg, jwt.MapClaims{
		"mail":     user["mail"],
		"password": user["password"],
	})
	fmt.Println("token :", token)
	json.NewEncoder(w).Encode(token)

	if out, err := token.SignedString(key); err == nil {
		fmt.Println(out)
	} else {
		fmt.Println("err : ", err)
	}
}

func handleRequests() {
	// creates a new instance of a mux router
	myRouter := mux.NewRouter().StrictSlash(true)
	// replace http.HandleFunc with myRouter.HandleFunc
	myRouter.HandleFunc("/", homePage).Methods("GET")
	myRouter.HandleFunc("/article/{id}", returnSingleArticle).Methods("GET")
	myRouter.HandleFunc("/articles", returnAllArticles).Methods("GET")
	myRouter.HandleFunc("/token", createToken).Methods("GET")

	myRouter.HandleFunc("/article/{id}", deleteArticle).Methods("DELETE")

	myRouter.HandleFunc("/article", createNewArticle).Methods("POST")

	myRouter.HandleFunc("/article/{id}", updateArticle).Methods("PUT")
	// finally, instead of passing in nil, we want
	// to pass in our newly created router as the second
	// argument
	log.Fatal(http.ListenAndServe(":8080", myRouter))
}

func init() {

	// On charge le .env
	err := godotenv.Load(".env")
	if err != nil {
		log.Fatal("Error loading .env file")
	}

	// On récupère la variable d'environnement MONGO_URI
	clientOptions := options.Client().ApplyURI(os.Getenv("MONGO_URI"))
	client, err := mongo.Connect(ctx, clientOptions)
	if err != nil {
		fmt.Println("premiere erreur")
		log.Fatal(err)
	}
	err = client.Ping(ctx, nil)
	if err != nil {
		fmt.Println("2 erreur")
		log.Fatal(err)
	}

	jwtKey, err = ioutil.ReadFile("pkcs8.key")
	if err != nil {
		fmt.Println("3 erreur")
		log.Fatal(err)
	}

	collection = client.Database("api-go").Collection("Articles")

	Articles = []typeApi.Article{
		{Id: "2", Title: "Hello 2", Desc: "Article Description", Content: "Article Content"},
		{Id: "1", Title: "Hello", Desc: "Article Description", Content: "Article Content"},
	}
}

func main() {
	fmt.Printf("Articles: %v\n", Articles)
	handleRequests()
}
