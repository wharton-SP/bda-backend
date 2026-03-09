# BDA Backend With C++

## Project Structure

```
BDA/
├── sql/
│   └── setup.sql
├── include/                 
│   ├── config/              
│   ├── controllers/         
│   ├── models/              
│   └── routes/              
├── src/                     
│   ├── controllers/
│   ├── models/
│   ├── routes/
│   └── **main.cpp**   
├── vcpkg.json
├── docker-compose.yml
├── .gitignore
├── README.md         
└── CMakeLists.txt 
```

## **Endpoint Summary**

| Method | Endpoint | Description |
|--------|----------|-------------|
| POST | `/auth/signin` | Create a user account |
| POST | `/auth/login` | User authentication |
| POST | `/suscribe/create` | Create a subscription |
| PUT | `/suscribe/update` | Update a subscription |
| DELETE | `/suscribe/delete` | Delete a subscription |
| GET | `/suscribe/getall` | List all subscriptions |
| GET | `/audit/logs` | List all audit logs |
| GET | `/audit/stat` | Audit statistics |
| GET | `/health` | API health check |


> **⚠️ Security Notice:** This project has no security implementation. Login and authentication should be handled on the frontend. The authentication table exists for structural purposes only.

> **Frontend Management:** Session management and user credentials should be handled by the frontend. Usernames should be stored in the browser cache if applicable.

> **Note:** Non-essential features have been intentionally omitted for this school project.

## **JSON Structure by Endpoint**

1- /auth/signin
```
{
    "username": "john_doe",
    "password": "monMotDePasse123",
    "role": "admin"  // or "user", "manager", etc.
}
```
2- /auth/login
```
{
    "username": "john_doe",
    "password": "monMotDePasse123"
}
```

3- /suscribe/create
```
{
    "matricule": 12345,
    "nom": "Jean Dupont",
    "droit_inscription": 50000,
    "utilisateur": "admin"
}
```

4- /suscribe/update
```
{
    "matricule": 12345,
    "nom": "Jean Dupont",
    "droit_inscription": 50000,
    "utilisateur": "admin"
}
```

5- /suscribe/delete
```
{
    "matricule": 12345,
    "utilisateur": "admin"
}
```

6- /suscribe/getall
```
No Request Body Required
```

7- /audit/logs
```
No Request Body Required
```

8- /audit/stat
```
No Request Body Required
```

9- /health
```
No Request Body Required
```