let footer = [];

const footerLinks = {
    Home: "/",
    About: "/about.html",
    Flashcards: "/flashcards.html",
    "Edit Residents": "/edit-residents.html",
    "Spreadsheet Services": "/spreadsheet-services.html",
}

Object.keys(footerLinks).forEach(function(item) {
    footer.push(`<li><a href = '${footerLinks[item]}'>${item}</a></li>`)
})

const footerHTML = `
<!--
<section class = "footer-top">
    <div class = "content">
        <h2>Let's Get Started!</h2>
        <h3>Text call to action!</h3>
    </div>
</section>
<div class="container">
    <img src = "/img/undraw_cat_epte.svg" alt = "CAT" class = "footerlogo">
    <div class="row footerinfo">
        <div class = "col-12 col-lg-4">
            <i class = "bi geo-alt-fill">
            </i>
        </div> 
    </div>
</div>
-->
<nav class="hidden-md-down">
    <ul></ul>
</nav>
`;

export {footer, footerHTML}