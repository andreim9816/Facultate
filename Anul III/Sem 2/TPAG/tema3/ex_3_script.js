const fs = require('fs');

const a = 10;
const pas = 0.065;
const fileExport = "ex_3_moebius_strip.obj";

let points = [];

let string = "# Blender v2.92.0 OBJ File: ''\n" +
    "# www.blender.org\n" +
    "mtllib " + fileExport + "\n";

for (let u = 0; u < 10; u += pas) {
    for (let v = -1; v < 27; v += pas) {
        const x = a * (Math.cos(v) + u * Math.cos(v / 2) * Math.cos(v));
        const y = a * (Math.sin(v) + u * Math.cos(v / 2) * Math.sin(v));
        const z = a * u * Math.sin(v / 2);

        const point = {
            x,
            y,
            z
        };

        points.push(point);
        string = string + "v " + x + " " + y + " " + z + "\n";
    }
}

string += "usemtl None\n" +
    "s off \n";

let facesString = "";
const len = points.length;
const rad = Math.floor(Math.sqrt(len));

for (let i = 0; i <= len - 5; ++i) {
    let nr1 = (i + 1) % len + 1;
    let nr2 = (i + rad) % len + 1;
    let nr3 = (i + rad - 1) % len + 1;
    let nr4 = (i + 1) % len + 1;
    facesString = facesString + "f " + nr1 + "// " + nr2 + "// " + nr3 + "// " + nr4 + "//\n";

    nr1 = (i + 1) % len + 1;
    nr2 = (i + 2) % len + 1;
    nr3 = (i + rad + 1) % len + 1;
    nr4 = (i + rad) % len + 1;
    facesString = facesString + "f " + nr1 + "// " + nr2 + "// " + nr3 + "// " + nr4 + "//\n";

    nr1 = (i + 1) % len + 1;
    nr2 = (i + 2) % len + 1;
    nr3 = (i - rad + 1 + len) % len + 1;
    nr4 = (i - rad + len) % len + 1;
    facesString = facesString + "f " + nr1 + "// " + nr2 + "// " + nr3 + "// " + nr4 + "//\n";

    nr1 = (i + 1) % len + 1;
    nr2 = (i - rad + len) % len + 1;
    nr3 = (i - rad - 1 + len) % len + 1;
    nr4 = (i - 1 + len) % len + 1;

    facesString = facesString + "f " + nr1 + "// " + nr2 + "// " + nr3 + "// " + nr4 + "//\n";

    nr1 = i + 1;
    nr2 = i + 2;
    nr3 = i + 3;
    nr4 = i + 4;
    facesString = facesString + "f " + nr1 + "// " + nr2 + "// " + nr3 + "// " + nr4 + "//\n";
}

string = string + facesString;

fs.writeFileSync(fileExport, string, (err) => {
    if (err)
        throw err;
});