const express = require("express");
const app = express();

app.set("view engine", "ejs");

app.get("/", (req, res) => {
    res.render("main");
});

app.listen("8080", () => {
    console.log("server running on 8080");
});