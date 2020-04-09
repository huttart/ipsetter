// Modules to control application life and create native browser window
const { app, BrowserWindow, Tray, Menu } = require('electron')
const path = require('path')
const AutoLaunch = require('auto-launch');
const fs = require('fs');
function createWindow() {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    show: false,
    webPreferences: {
      nodeIntegration: true
    },
  })

  // and load the index.html of the app.
  mainWindow.loadFile('index.html')

  // Open the DevTools.
  mainWindow.webContents.openDevTools()

  mainWindow.webContents.on('crashed', (e) => {
    app.relaunch();
    app.quit();
  });

  mainWindow.on('minimize', function (event) {
    event.preventDefault();
    mainWindow.hide();
  });

  // mainWindow.hide();

  mainWindow.on('closed', function () {
    app.quit();
  });
}


app.on('ready', () => {
  createWindow();
  let autoLaunch = new AutoLaunch({
    name: 'IP SETTER',
    path: app.getPath('exe'),
  });
  autoLaunch.isEnabled().then((isEnabled) => {
    if (!isEnabled) autoLaunch.enable();
  });

  var image = path.join(__dirname,'./icon.png');
  // if (fs.existsSync(`./icon.png`)) {
  //   image = './icon.png';
  // } else {
  //   image = './resources/app/icon.png';
  // }


  // tray = new Tray('./icon.png');
  tray = new Tray(image);
  const contextMenu = Menu.buildFromTemplate([
    {
      label: 'Close', click: function () {
        app.quit();
      }
    },
  ])
  tray.setToolTip('GMC IP SETTER is running.')
  tray.setContextMenu(contextMenu);
})

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})

app.on('activate', function () {
  if (BrowserWindow.getAllWindows().length === 0) createWindow()
})

