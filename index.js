const express = require("express");
const app = express();
const fs = require('fs');
const bodyParser = require('body-parser');
const Decimal = require('decimal.js');

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());


app.set("view engine", "ejs");

app.get("/", (req, res) => {
    const users = JSON.parse(fs.readFileSync("./db.json")).data;
    res.render("main", {users});
});

app.post("/changeVal", (req, res) => {
    if (req.body.password == "lixoinatorUser"){
        const users = JSON.parse(fs.readFileSync("./db.json"));
        const index = Number(req.body.user.index);

        vl = new Decimal(req.body.value);
        credit = new Decimal(users.data[index].credit);
        users.data[index].credit = credit.minus(vl);

        fs.writeFileSync("./db.json", JSON.stringify(users));

        res.sendStatus(200);
    }else{
        res.sendStatus(400);
    }
});

app.post("/addVal", (req, res) => {
    if (req.body.password == "lixoinatorUser"){
        const users = JSON.parse(fs.readFileSync("./db.json"));
        const index = Number(req.body.index);

        vl = new Decimal(0.05);
        credit = new Decimal(users.data[index].credit);
        users.data[index].credit = credit.plus(vl);

        fs.writeFileSync("./db.json", JSON.stringify(users));

        res.sendStatus(200);
    }else{
        res.sendStatus(400);
    }
});

app.get("/getUsers", (req, res)=> {
    const users = JSON.parse(fs.readFileSync("./db.json")).data;
    res.send(users);
});

app.listen("8080", () => {
    console.log("server running on 8080");
});
