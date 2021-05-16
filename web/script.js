const APPID = "SocialDistancingEscalator";
const KEY = "5w6kDMdXJnP8NQk";
const SECRET = "CHh4GUc8UAAXRonPvv13M5uyX";

const ALIAS = "HTML_web";
const thing = "NodeMCU";


var maxNum = maxNum;

var microgear = Microgear.create({
    key: KEY,
    secret: SECRET,
    alias: ALIAS
});

var curNum = 0;

document.getElementById("curPeople").value = curNum;

function updateCapacity() {
    if (document.getElementById("cap").value == '') {
        alert("Please enter the maximum capacity.")
    } else {
        maxNum = document.getElementById("cap").value;
        console.log(maxNum);
        document.getElementById("cap").value = '';
        document.getElementById("displayCap").innerHTML = "Maximum capacity: " + maxNum;
    }
}

// const ExplicitPrevention = function (event) {
//     var keyPressed = event.keyCode || event.which;
//     if (keyPressed === 13) {
//         updateCapacity();
//     }
// }

function CheckCap(n) {
    if (n>maxNum) {
        microgear.chat(thing,"RED");
    } else {
        microgear.chat(thing,"YELLOW");
    }
}

microgear.on('message', function(topic,msg) {
    document.getElementById("raw_data").innerHTML = "msg:" + msg;
});

microgear.on('connected', function() {
    microgear.setAlias(ALIAS);
    console.log("Connected to NETPIE.")
    // setInterval(function() {
    //     microgear.chat("htmlgear","Hello from myself at "+Date.now());
    // },5000);
});

microgear.on('present', function(event) {
    console.log(event);
});

microgear.on('absent', function(event) {
    console.log(event);
});

microgear.resettoken(function(err){
    microgear.connect(APPID)
});