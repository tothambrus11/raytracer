import algebra, {Equation, Expression} from "algebra.js";

let input = "(a*(o_x+d_x*i-u)+b*(o_y+d_y*i-v)+c*(o_z+d_z*i-w))^2 + (d*(o_x+d_x*i-u)+e*(o_y+d_y*i-v)+f*(o_z+d_z*i-w))^2 - r*r".replace(/_/g, "XX");

let res = algebra.parse(input).toString()
let tags = res.replace(/\s([+\-])\s/g, ' $1').split(' ');

let i0 = [];
let i1 = [];
let i2 = [];

for (let t of tags) {
    if (t.includes("i^2")) {
        t = t.replace("i^2", '')
        i2.push(t);
    } else if (t.includes("i")) {
        t = t.replace("i", '')
        i1.push(t);
    } else {
        i0.push(t);
    }
}

function programifyExpression(e) {
    let res = "";
    e = e.replace(/XX/g, "_");
    let e1 = e;
    for (let i = 0; i < e.length; i++) {
        let c = e.charAt(i);
        if (res !== "+ " && res !== "- " && c !== '+' && c !== "-" && c !== "^" && isNaN(c) && c != "_" && (i <= 0 || e.charAt(i - 1) != "_")) {
            res += " * ";
        }

        res += c;

        if (res.length === 1 && (res.startsWith('-') || res.startsWith('+'))) {
            res += " ";
        }
    }

    let res2 = res;
    for (let i = 0; i < res.length; i++) {
        if (res.charAt(i) === "^") {
            let startPos;
            for (startPos = i; startPos >= 0; startPos--) {
                if (res.charAt(startPos) === " ") {
                    break;
                }
            }
            let varName = res.substring(startPos + 1, i);
            res2 = res2.replace(varName + "^2", varName + " * " + varName)
        }
    }
    console.log(res2);
}

console.log("double coeff_c = ")
i0.forEach(e => {
    programifyExpression(e);
})
console.log(";");

console.log("double coeff_b = ")
i1.forEach(e => {
    programifyExpression(e);
})
console.log(";")

console.log("double coeff_a = ")
i2.forEach(e => {
    programifyExpression(e);
})
console.log(";")