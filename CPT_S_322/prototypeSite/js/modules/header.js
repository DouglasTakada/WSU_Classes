let header = [];

const headerLinks = {
    Home: "/",
    About: "/about.html",
    Flashcards: "/flashcards.html",
    "Edit Residents": "/edit-residents.html",
    "Spreadsheet Services": "/spreadsheet-services.html",
}

const headerSublinks = {
    Flashcards: {
        "Create":"/create-flashcards.html",
        "Edit":"/edit-flashcards.html",
        "View":"/view-flashcards.html"
    }
}

Object.keys(headerLinks).forEach(function(item) {
    if (headerSublinks[item]) {
    let subNav = `<li><a href = '${headerLinks[item]}'>${item}</a><ul class ='submenu'>`;
        Object.keys(headerSublinks[item]).forEach(
            function (subitem) {
                subNav += `<li><a href = '${headerSublinks[item][subitem]}'>${subitem}</a></li>`;
            }.bind(this)
        )
        header.push(subNav);
    } else {
        header.push(`<li><a href = '${headerLinks[item]}'>${item}</a></li>`)
    }
})

const headerHTML =`
<div class="container">
    <div class="logo">
        <a href="/"><img src="/img/RA_Logo.png" alt="RA App Logo"></a>
    </div>
    <div class="subheader">
        <ul>
            <!-- CANVAS/MYWSU icon? -->
            <li><a href="" target="_blank"><i class="bi-mortarboard"></i></a></li>
            <!-- Our github repository icon? -->
            <li><a href="" target="_blank"><i class="bi-github"></i></a></li>
            <!-- README icon? -->
            <li><a href="" target="_blank"><i class="bi-card-text"></i></a></li>
        </ul>
    </div>
    <nav>
        <ul></ul>
    </nav>
</div>
`;
export {header, headerHTML}
