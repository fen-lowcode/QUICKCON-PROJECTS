
function storeInfoToSession() {
     var takeInput = (id) => {
        const elementVal = document.getElementById(id);
        return elementVal.innerText
    }

   const data = {
        ID: clientData.ID, 
        CLIENTS_NAME: takeInput('view-name'),
        PLAN: takeInput('view-plan'),
        CREDENTIALS: takeInput('view-creds'),
        DATE_APPLIED: takeInput('view-applied'),
        AGE: takeInput('view-age'),
        SEX: takeInput('view-sex'),
        OCCUPATION: takeInput('view-job'),
        DATE_OF_BIRTH: takeInput('view-dob'),
        PLACE_OF_BIRTH: takeInput('view-pob'),
        ADDRESS: takeInput('view-address'),
        CONTACT_NO: takeInput('view-contact'),
        SOCIAL_MEDIA: takeInput('view-social'),
        OPTICAL_INFO: takeInput('view-optical'),
        INSTALLED_BY: takeInput('view-tech'),
        REMARKS: takeInput('view-remarks'),
        SC_CONNECTOR: takeInput('view-sc'),
        FIBER_DROP: takeInput('view-fiber'),
        TAPPING_CLIP: takeInput('view-clip'),
        CABLE_TIE: takeInput('view-tie'),
        F_CLAMP: takeInput('view-fclamp')
    };

    localStorage.setItem('currentClient',JSON.stringify(data));
}