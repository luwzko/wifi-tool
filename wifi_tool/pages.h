#ifndef pages_h
#define pages_h

const char root_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <style>
        html {
            height: 100%;
            background: linear-gradient(#141e30, #243b55);
            color: white;
            font-family: sans-serif;
    	}
        .enigma_title {
            font-family: 'Impact';  
            font-size: 100px; 
            font-weight: lighter; 
            text-align: center; 
            letter-spacing: -1px; 
            line-height: 1; 
        }
        .mod_title {
            font-size: 20px;
            font-weight: 600;
            text-align: center;
            margin-bottom: 5px;
        }
        .mod_form1 {
            float:left;
            position: relative;
            margin: 50px;
            padding: 5px 10px;
            outline: solid 2px white;
            
            width: 250px;
            height: 300px;
        }
        .mod_form2 {
            float:  left;
            position: relative;
            margin: 50px;
            padding: 5px 10px;
            outline: solid 2px white;
        
            width: 500px;
            height: 300px;
        }
        div.scroll {
            position: absolute;
            width: 95%;
            height: 240px;
            
            overflow-x: auto;
            overflow-y: scroll;
            border: 2px white solid;
            
            left: 10px;
            right: 10px;
        }
        .action_button { position: absolute; top: 280px;}
        table {width: 100%;}
        td {text-align: center;}
    </style>
    <div class="enigma_title">ENIGMA</div>
</head>
<body>
    <div class="mod_form1" id="beacon">
        <div class="mod_title">Beacon Spammer</div>
        <div>
            <form action="/spammer/arm" method="get">
                <input id="ssid" name="ssid" type="text" placeholder="SSID"><br>
                <input id="ap_count" name="ap_count" type="number" placeholder="Number of APs"><br>
                <button type="submit">ARM</button>
            </form>
        </div>
        <div>
            <form action="/spammer/toggle" method="get" id="toggle_form">
                <button class="action_button" type="submit">Toggle</button>
            </form>
        </div>
    </div>
    <div class="mod_form2" id="scan">
        <div class="mod_title">Scan</div>
        <div class="scroll">
            <table class="mod_table" id="table_res">
            <tr><th>SSID</th><th>BSSID</th><th>RSSI</th><th>Ch</th><th>Enc</th><th>Hidden</th></tr>
            </table>
        </div>
        <form action="/scanner/start" method="get">
            <button class="action_button" type="submit">START</button>
        </form>
    </div>
    <script>
        var scan_table = new XMLHttpRequest();
        scan_table.open("GET", "/scanner/results");
        scan_table.send();

        scan_table.onload = function() {
            if (scan_table.status == 200) {
                document.getElementById("table_res").innerHTML += scan_table.response;
            }
        };
        function refreshPage() {
            window.location = window.location.href;
        }
    </script>
</body>
</html>)=====";
#endif