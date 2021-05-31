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

function updateCapacity(){
    if (curNum<=maxNum*33/100) {
        document.getElementById("box").style.color= "darkgreen";
    } else if (curNum<=maxNum*66/100) {
        document.getElementById("box").style.color= "darkgoldenrod";
    } else {
        document.getElementById("box").style.color= "darkred";
    }
}

function updateMaxCapacity() {
    if (document.getElementById("cap").value == '') {
        alert("Please enter the maximum capacity.")
    } else {
        maxNum = document.getElementById("cap").value;
        document.getElementById("cap").value = '';
        document.getElementById("displayCap").innerHTML = "Maximum capacity: " + maxNum;
    }
    updateCapacity();
}

function CheckCap(n) {
    console.log('f:checkCap')
    if (n>=maxNum) {
        microgear.chat(thing,"RED");
        console.log(n + ' : RED')
        document.getElementById("maxReach").innerHTML = "Maximum Capacity Reached"
    } else {
        microgear.chat(thing,"YELLOW");
        console.log(n + ' : YELLOW')
        document.getElementById("maxReach").innerHTML = ""
    }
}

microgear.on('message', function(topic,msg) {
    console.log('message ',msg);
    var msg1 = msg[0]+msg[1];
    console.log(msg1)
    if (msg1 == "+1") {
        
        curNum++;
        if (curNum>maxNum) curNum=maxNum;
    } else if (msg1 == "-1") {
        curNum--;
        if (curNum<0) curNum=0;
    }
    document.getElementById("curPeople").innerHTML = curNum;
    updateCapacity();
    CheckCap(curNum);
});

microgear.on('connected', function() {
    microgear.setAlias(ALIAS);
    console.log("Connected to NETPIE.")
    // setInterval(function() {
    //     microgear.chat("htmlgear","Hello from myself at "+Date.now());
    // },5000);
});

microgear.on('present', function(event) {
    console.log('present ' + event);
});

microgear.on('absent', function(event) {
    console.log('absent ' + event);
});

microgear.resettoken(function(err){
    microgear.connect(APPID)
});