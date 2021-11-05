var path = require('path');
var _a = require('electron'), app = _a.app, BrowserWindow = _a.BrowserWindow;

function createWindow() {
    var window = new BrowserWindow({
        width: 800,
        height: 600,
		webPreferences: {
			preload: path.join(__dirname, 'preload.js')
		}
    });

	window.loadFile('index.html');
}

app.whenReady().then(function () {
    console.log('App ready');

	createWindow();
});

app.on('window-all-closed', function () {
    // On MacOS the application does not automatically quit when all windows are destroyed
    // Electron places the responsibility for this cross-platform behavior in your hand
    if (process.platform !== 'darwin') {
        app.quit();
    }
});
