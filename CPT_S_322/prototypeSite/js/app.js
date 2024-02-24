import {header, headerHTML} from "./modules/header.js" 
import {footer, footerHTML} from "./modules/footer.js" 

const headerLayout = document.querySelector("header");
headerLayout.innerHTML = headerHTML;

const headerDiv = document.querySelectorAll("header nav ul");
header.forEach((item) => {
    headerDiv.forEach((div) => {
        div.innerHTML += item;
    })
})

const footerLayout = document.querySelector("footer");
footerLayout.innerHTML = footerHTML;

const footerDiv = document.querySelectorAll("footer nav ul");
footer.forEach((item) => {
    footerDiv.forEach((div) => {
        div.innerHTML += item;
    })
})

const navItems = document.querySelectorAll('header nav li');
navItems.forEach((item) => {
    let submenu = item.querySelector("ul");
    if (submenu) {
        item.addEventListener("mouseenter", function(){
            submenu.classList.add("active");
        })
        item.addEventListener("mouseleave", function(){
            submenu.classList.remove("active");
        })
    }
})

const heroCTAItems = document.querySelectorAll('.herocta');
if(heroCTAItems.length > 0) {
    heroCTAItems.forEach((item) => {
        item.addEventListener("mouseenter", function() {
            item.classList.add("active")
        })
        item.addEventListener("mouseleave", function() {
            item.classList.remove("active")
        })
    })
}

const mobilemenu = document.querySelector(".mobilemenuicon");
mobilemenu.addEventListener("click", function () {
	this.classList.toggle("bi-list");
	this.classList.toggle("bi-x-circle");
	const mobilemenu = document.querySelector(".mobilemenu nav");
	mobilemenu.classList.toggle("active");
});
