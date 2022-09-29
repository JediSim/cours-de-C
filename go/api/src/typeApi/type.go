package typeApi

type Article struct {
	Id      string `json:"Id"`
	Title   string `json:"Title"`
	Desc    string `json:"desc"`
	Content string `json:"content"`
}

type User struct {
	Email    string `json:"email"`
	Password string `json:"password"`
}
