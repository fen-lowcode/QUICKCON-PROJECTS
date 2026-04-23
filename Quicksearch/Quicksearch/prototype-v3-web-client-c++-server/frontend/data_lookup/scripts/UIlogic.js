/* ============================================================
    1. CORE UTILITIES (The "Pointers" & "Sanity Checks")
============================================================ */

// Helper to write data to the DOM. Checks if ID exists before writing.
function writeToUI(elementId, value) {
    let target = document.getElementById(elementId);
    if (target !== null) {
        // If value is null or empty, use a placeholder
        if (value === undefined || value === null || value === "") {
            target.innerText = "---";
        } else {
            target.innerText = value;
        }
    }
}

/* ============================================================
    2. VIEW CONTROLLER (Template Loading)
============================================================ */
function loadTemplates(templateId) {

    // kills spelling correction that pesky red line squigles
    document.querySelectorAll('[contenteditable]').forEach(el => {
        el.setAttribute('spellcheck', 'false');
    });

    let container = document.getElementById('app-container');
    let template = document.getElementById(templateId);

    if (template === null) return;

    container.innerHTML = '';
    let instance = template.content.cloneNode(true);
    container.appendChild(instance);

    // Dynamic Sidebar State Management
    let navItems = document.querySelectorAll('.nav-item');
    navItems.forEach(item => {
        item.classList.remove('active');
        
        // Extract the keywords (e.g., 'list', 'profile', 'history')
        let text = item.innerText.toLowerCase();
        
        // If the template ID (view-payment-history) contains the word 'history'
        if (templateId.toLowerCase().includes(text.split(' ')[text.split(' ').length - 1])) {
            item.classList.add('active');
        }
    });
}

/* ============================================================
    3. DATA FETCHING (C++ Backend Interaction)
============================================================ */

function renderTableRows(dataList) {
    let tableBody = document.getElementById('tableBody');
    let htmlBuilder = "";

    for (let i = 0; i < dataList.length; i++) {
        let c = dataList[i];
        
        htmlBuilder += `
            <tr>
                <td><button class="delete-btn" onclick="deleteCustomer(event)"><img src="../assets/trasbhin.png"></button></td>
                <td>${c.ID}</td>
                <td>${c.CLIENTS_NAME}</td>
                <td>${c.CREDENTIALS}</td>
                <td>${c.ADDRESS}</td>
                <td>${c.PLAN}</td>
                <td>${c.DATE_APPLIED}</td>
                <td>${c.CONTACT_NO}</td>
                <td>${c.AGE}</td>
                <td>${c.SEX}</td>
                <td>${c.SOCIAL_MEDIA}</td>
                <td>${c.OCCUPATION}</td>
                <td>${c.DATE_OF_BIRTH}</td>
                <td>${c.PLACE_OF_BIRTH}</td>
                <td>${c.OPTICAL_INFO}</td>
                <td>${c.SC_CONNECTOR}</td>
                <td>${c.FIBER_DROP}</td>
                <td>${c.TAPPING_CLIP}</td>
                <td>${c.CABLE_TIE}</td>
                <td>${c.F_CLAMP}</td>
                <td>${c.REMARKS}</td>
                <td>${c.INSTALLED_BY}</td>
            </tr>`;
    }
    tableBody.innerHTML = htmlBuilder;
    document.getElementById('rowCount').innerText = dataList.length + " Records Loaded";
}

/* ============================================================
    4. EVENT HANDLING (The Bridge)
============================================================ */
document.addEventListener('click', function(e) {
    let row = e.target.closest('#tableBody tr');
    let isDelete = e.target.closest('.delete-btn');

    if (row === null || isDelete !== null) return;

    // Extracting data from table columns (Indices match <thead>)
    let cells = row.cells;
    let data = {

        ID:             cells[1].innerText,  
        CLIENTS_NAME:   cells[2].innerText,
        CREDENTIALS:    cells[3].innerText,
        ADDRESS:        cells[4].innerText,
        PLAN:           cells[5].innerText,
        DATE_APPLIED:   cells[6].innerText,
        CONTACT_NO:     cells[7].innerText,
        AGE:            cells[8].innerText,
        SEX:            cells[9].innerText,
        SOCIAL_MEDIA:   cells[10].innerText,
        OCCUPATION:     cells[11].innerText,
        DATE_OF_BIRTH:  cells[12].innerText,
        PLACE_OF_BIRTH: cells[13].innerText,
        OPTICAL_INFO:   cells[14].innerText,
        SC_CONNECTOR:   cells[15].innerText,
        FIBER_DROP:     cells[16].innerText,
        TAPPING_CLIP:   cells[17].innerText,
        CABLE_TIE:      cells[18].innerText,
        F_CLAMP:        cells[19].innerText,
        REMARKS:        cells[20].innerText,
        INSTALLED_BY:   cells[21].innerText,

    };

    openProfile(data);
});


function openProfile(data) {
    loadTemplates('view-profile');
    
    let profileCard = document.getElementById("profile-modal-background");
    profileCard.style.display = "flex";

    // Header logic

     // Direct Mapping to the Template IDs we created

    writeToUI('view-name',    data.CLIENTS_NAME);
    writeToUI('customer-name',data.CLIENTS_NAME);
    writeToUI('view-id',      data.ID);
    writeToUI('view-plan',    data.PLAN);
    writeToUI('view-creds',   data.CREDENTIALS);
    writeToUI('view-applied', data.DATE_APPLIED);
    writeToUI('view-age',     data.AGE);
    writeToUI('view-sex',     data.SEX);
    writeToUI('view-job',     data.OCCUPATION);
    writeToUI('view-dob',     data.DATE_OF_BIRTH);
    writeToUI('view-pob',     data.PLACE_OF_BIRTH);
    writeToUI('view-address', data.ADDRESS);
    writeToUI('view-contact', data.CONTACT_NO);
    writeToUI('view-social',  data.SOCIAL_MEDIA);
    writeToUI('view-optical', data.OPTICAL_INFO);
    writeToUI('view-tech',    data.INSTALLED_BY);
    writeToUI('view-remarks', data.REMARKS);
    writeToUI('view-sc',      data.SC_CONNECTOR);
    writeToUI('view-fiber',   data.FIBER_DROP);
    writeToUI('view-clip',    data.TAPPING_CLIP);
    writeToUI('view-tie',     data.CABLE_TIE);
    writeToUI('view-fclamp',  data.F_CLAMP);
}

function closeProfile() {
    let profileCard = document.getElementById("profile-modal-background");
    profileCard.style.display = "none";
}

function openHistory(data) {
    loadTemplates('view-payment-history')
}

/* ============================================================
    5. SEARCH LOGIC (Imperative Logic)
============================================================ */
function filterTable() {
    let input = document.getElementById("tableSearch").value.toUpperCase().trim().split(" "); // split into words
    let rows = document.querySelectorAll("#tableBody tr");
    let count = 0;

    rows.forEach(row => {

        let text = row.textContent.toUpperCase();
        let match = input.every(word => text.includes(word));

        if (match) { row.style.display = ""; count++;
        } else { row.style.display = "none"; }
    });

    document.getElementById('rowCount').innerText = count + " Records Found";
}

// Entry Point
window.onload = function() {
    loadTemplates('view-client-list');   
    fetchClientmasterList();
};

//  TEMPORARY FIELD
// ==============================================================
