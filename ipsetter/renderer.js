

const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const cmd = require('node-cmd')
const isIp = require('is-ip');
var port = new SerialPort('com4', { baudRate: 9600 })
const parser = new Readline()
const network = require('network');
var ip = '';
var ipface;
var gate_way;

port.pipe(parser)


parser.on('data', line => {
    console.log(line.length);
    var ip_sections = line.split('.');
    var tmp_ip = '';
    var i = 0;
    ip_sections.forEach(element => {
        tmp_ip += parseInt(element);
        if (i < ip_sections.length - 1) {
            tmp_ip += '.';
        }
        i++;
    });
    console.log(tmp_ip);
    if (isIp.v4(tmp_ip)) {
        console.log('Setting ip Address');
        console.log('ip = ' + tmp_ip);
        console.log('gateway = ' + gate_way);
        console.log('netmask = ' + ipface.netmask);

        cmd.get('netsh interface ip set address "Ethernet" static ' + tmp_ip + ' ' + ipface.netmask + ' ' + gate_way, function (err, data, stderr) {
            console.log(err);
            console.log(data);
        });
    }
});

setInterval(() => {
    // console.log(port);
    if (!port.isOpen) {
        port = new SerialPort('com4', { baudRate: 9600 });
        port.pipe(parser);
    }
    GetCurrentIp();
    network.get_gateway_ip(function (err, ip) {
        // console.log(err || ip); // err may be 'No active network interface found.'
        gate_way = ip;
    })
    
}, 2000);


function GetCurrentIp() {
    var os = require('os');
    var ifaces = os.networkInterfaces();
    Object.keys(ifaces).forEach(function (ifname) {
        var alias = 0;
        ifaces[ifname].forEach(function (iface) {
            if ('IPv4' !== iface.family || iface.internal !== false) {
                return;
            }
            if (alias >= 1) {
            } else {
                ipface = iface;
                ip = iface.address;
                var ip_sections = ip.split('.');
                ip = '';
                var i = 0;
                ip_sections.forEach(element => {
                    if (element.length == 1) {
                        ip_sections[i] = '00' + element;
                    }
                    if (element.length == 2) {
                        ip_sections[i] = '0' + element;
                    }
                    ip += ip_sections[i];
                    if (i < ip_sections.length - 1) {
                        ip += '.';
                    }
                    i++;
                });
                // console.log(ip);
                port.write(ip);
            }
            ++alias;
        });
    });
}