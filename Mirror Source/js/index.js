'use strict';

var app = {
    initialize: function() {
        //this.bindEvents();
    },
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    onDeviceReady: function() {
        app.refreshDeviceList();
    },
    refreshDeviceList: function() {
        bluetoothSerial.list(app.onDeviceList, app.onError);
    },
    onDeviceList: function(devices) {
        var option;
        alert('found!');

        devices.forEach(function(device) {
            var string = '<b>' + device.name + '</b><br/>' + device.id;
            document.write(string);
        });

        if (devices.length === 0) {
            alert('no devices');
        } else {
            alert('found some devices');
        }

    },
    onError: function(reason) {
        alert('error');
    }
}