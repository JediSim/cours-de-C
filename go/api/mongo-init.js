db = db.getSiblingDB(_getEnv("MONGO_INITDB_DATABASE"));
db.createUser({
  user: _getEnv("MONGO_INITDB_USER"),
  pwd: _getEnv("MONGO_INITDB_PASSWORD"),
  roles: [
    {
      role: "readWrite",
      db: _getEnv("MONGO_INITDB_DATABASE"),
    },
  ],
});
