
document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault();

    const firstName = document.getElementById("fname").value;
    const lastName = document.getElementById("lname").value;
    const password = document.getElementById("psw").value;

    try {
        const response = await fetch('http://192.168.1.22:2222/auth/session', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ 
                fname: firstName,
                lname: lastName,
                psw: password 
            })
        });

        const data = await response.json();

        if (response.ok) {

            localStorage.setItem('JWT', data.token);

            // Redirect
            window.location.href = "./data_lookup/index.html";

        } else {
            // Handle server-side errors (e.g., wrong password)
            alert("Login Failed: " + (data.message || "Invalid credentials"));
        }

    } catch (error) {
        console.error("Failed to connect to backend:", error);
        alert("Error: Could not reach the backend server.");
    }
});