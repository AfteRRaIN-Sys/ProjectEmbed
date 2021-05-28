const APPID = "SocialDistancingEscalator";
const KEY = "5w6kDMdXJnP8NQk";
const SECRET = "CHh4GUc8UAAXRonPvv13M5uyX";

const ALIAS = "HTML_web";
const thing = "NodeMCU";


var maxNum = maxNum;
var curNum = 0;

var microgear = Microgear.create({
    key: KEY,
    secret: SECRET,
    alias: ALIAS
});

function updateCapacity() {
    if (document.getElementById("cap").value == '') {
        alert("Please enter the maximum capacity.")
    } else {
        maxNum = document.getElementById("cap").value;
        console.log(maxNum);
        console.log(curNum);
        document.getElementById("cap").value = '';
        document.getElementById("displayCap").innerHTML = "Maximum capacity: " + maxNum;
        if (curNum<=maxNum*33/100) {
            document.getElementById("box").style.color= "darkgreen";
        } else if (curNum<=maxNum*66/100) {
            document.getElementById("box").style.color= "darkgoldenrod";
        } else {
            document.getElementById("box").style.color= "darkred";
        }
        CheckCap(curNum);
    }
}

// const ExplicitPrevention = function (event) {
//     var keyPressed = event.keyCode || event.which;
//     if (keyPressed === 13) {
//         updateCapacity();
//     }
// }

function CheckCap(n) {
    if (n>=maxNum) {
        microgear.chat(thing,"RED");
    } else {
        microgear.chat(thing,"YELLOW");
    }
}

microgear.on('message', function(topic,msg) {
    document.getElementById("raw_data").innerHTML = "msg:" + msg;
    if (msg == "+1") {
        curNum++;
        if (curNum>maxNum) curNum=maxNum;
    } else if (msg == "-1") {
        curNum--;
        if (curNum<0) curNum=0;
    }
    document.getElementById("curPeople").innerHTML = curNum;
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