# Session Summary — 2026-04-27 — GraphQL with FastAPI & Ariadne

## What We Covered

Built a GraphQL API from scratch using FastAPI and Ariadne. Covered core GraphQL concepts — schema design, queries, mutations, nested types, field-level resolvers, and how GraphQL's single-endpoint model differs from REST.

---

## Key Concepts Learned

- **GraphQL Single Endpoint**
  - All queries and mutations go through one URL (`/graphql`) via POST
  - The operation type (`query` vs `mutation`) is declared in the request body, not the URL
  - Doc: [GraphQL — Queries and Mutations](https://graphql.org/learn/queries/)

- **SDL — Schema Definition Language**
  - GraphQL schemas are declared in a typed language called SDL
  - `type Query` is the root entry point for fetching data — not a data model
  - Type names must be PascalCase per the GraphQL spec
  - Doc: [GraphQL — Schemas and Types](https://graphql.org/learn/schema/)

- **Separating Types from Query**
  - `type Article` is a data model — it describes the shape of an object
  - `type Query` is the entry point — it describes what you can fetch and with what arguments
  - Conflating the two is a common beginner mistake

- **Arguments in SDL**
  - Fields can accept arguments: `article(id: Int!): Article`
  - `!` means non-null — the argument or field is required
  - Doc: [GraphQL — Arguments](https://graphql.org/learn/queries/#arguments)

- **List Types**
  - `[Article]` declares a field that returns a list of Articles
  - Doc: [GraphQL — Lists and Non-Null](https://graphql.org/learn/schema/#lists-and-non-null)

- **QueryType (Ariadne)**
  - Ariadne's `QueryType()` binds resolver functions to fields on `type Query`
  - `@query.field("article")` registers the resolver for `Query.article`
  - Doc: [Ariadne — Resolvers](https://ariadnegraphql.org/docs/resolvers)

- **Resolver Signature**
  - Every Ariadne resolver receives `(obj, info, **kwargs)`
  - `obj` — parent object (None for root Query resolvers)
  - `info` — request context, schema info
  - Query arguments arrive as keyword arguments after `obj` and `info`
  - `*_` can be used to swallow `obj` and `info` when not needed

- **ObjectType (Ariadne)**
  - Used to attach field-level resolvers to non-root types like `Article`
  - `ObjectType("Article")` binds resolvers to fields on `type Article`
  - Must be passed to `make_executable_schema` or resolvers are ignored
  - Doc: [Ariadne — Object Types](https://ariadnegraphql.org/docs/resolvers#bindable-objects)

- **Nested Type Resolution**
  - `user: User!` on `Article` is an output type — not an input requirement
  - GraphQL resolves nested fields **lazily** — only when the client asks for them
  - The `Article.user` resolver receives the parent article dict as `obj`, uses `obj["user_id"]` to look up the full User
  - No data duplication — types stay independent, resolvers wire them together at request time

- **One-to-Many Relationships**
  - Foreign key lives on the "many" side — `article_id` on `Comment`, not the other way around
  - Same principle as Django ForeignKey / PostgreSQL FK constraints
  - `Article.comments` resolver filters `mock_comments` by `article_id == obj["id"]`

- **MutationType (Ariadne)**
  - `MutationType()` binds resolvers to fields on `type Mutation`
  - Mutation arguments arrive as keyword arguments — no request body parsing needed
  - Mutations should return the created/updated object so clients can immediately query fields on it
  - Doc: [GraphQL — Mutations](https://graphql.org/learn/queries/#mutations)

- **make_executable_schema**
  - Wires together SDL type definitions and all resolver bindings
  - Must include every bindable: `make_executable_schema(type_def, query, mutation, article_type)`
  - Doc: [Ariadne — make_executable_schema](https://ariadnegraphql.org/docs/api-reference#make_executable_schema)

- **app.mount() in FastAPI**
  - Attaches a separate ASGI app at a given path
  - FastAPI delegates all `/graphql` requests to Ariadne's own ASGI app entirely
  - Different from a regular route — FastAPI doesn't process the request itself
  - Doc: [FastAPI — Sub Applications](https://fastapi.tiangolo.com/advanced/sub-applications/)

---

## Problems We Worked Through

- **`type Query` used as a data model** — confused the root entry point with an Article type definition. Fixed by separating `type Article` and `type Query` with proper field references.
- **Wrong resolver return type** — returning a list `[...]` instead of a single object for `article(id)`. Fixed by using `next()` with a default of `None`.
- **`next()` confusion** — unfamiliar with using a generator inside `next()` as a safe alternative to `list[0]`. Resolved by comparing it to the familiar list comprehension pattern.
- **Duplicate function names** — multiple resolvers sharing the same Python function name, causing silent overwrites. Fixed by giving each resolver a descriptive unique name.
- **Resolver signature** — `*_` swallowing arguments including `info`. Clarified that `*_` correctly absorbs `obj` and `info` when unused, with query arguments arriving as explicit keyword args.
- **Fetching user inside article resolver** — attempting to do too much in one resolver instead of delegating to a field-level `ObjectType` resolver. Fixed by returning just the article dict and letting `article_type.field("user")` handle the lookup lazily.
- **`user_id` vs `user` confusion** — clarified that `user: User!` in the schema is an output type declaration, not an input requirement. `user_id` in the dict is all the resolver needs to look up the full User.

---

## Code Patterns Introduced

```python
# Safe single-item lookup — returns None instead of crashing on empty list
next((a for a in mock_articles if a["id"] == id), None)

# Field-level resolver on a non-root type
# obj is the parent Article dict — GraphQL passes it automatically
article_type = ObjectType("Article")

@article_type.field("user")
def resolve_article_user(obj, *_):
    return next((u for u in mock_users if u["id"] == obj["user_id"]), None)

# One-to-many: find all comments belonging to an article
@article_type.field("comments")
def resolve_article_comments(obj, *_):
    return [c for c in mock_comments if c["article_id"] == obj["id"]]

# Mutation resolver — arguments arrive as keyword args, not request body
@mutation.field("createArticle")
def resolve_create_article(_, info, title, content, user_id):
    new_article = {
        "id": len(mock_articles) + 1,  # naive ID — fine for mocks only
        "title": title,
        "content": content,
        "user_id": user_id
    }
    mock_articles.append(new_article)
    return new_article  # return created object so client can query fields on it

# Wire everything together
schema = make_executable_schema(type_def, query, mutation, article_type)
```

---

## References

- [GraphQL — Queries and Mutations](https://graphql.org/learn/queries/)
- [GraphQL — Schemas and Types](https://graphql.org/learn/schema/)
- [GraphQL — Arguments](https://graphql.org/learn/queries/#arguments)
- [GraphQL — Lists and Non-Null](https://graphql.org/learn/schema/#lists-and-non-null)
- [GraphQL Spec — Type System](https://spec.graphql.org/October2021/#sec-Types)
- [Ariadne — Resolvers](https://ariadnegraphql.org/docs/resolvers)
- [Ariadne — Object Types](https://ariadnegraphql.org/docs/resolvers#bindable-objects)
- [Ariadne — make_executable_schema](https://ariadnegraphql.org/docs/api-reference#make_executable_schema)
- [FastAPI — Sub Applications / Mounting](https://fastapi.tiangolo.com/advanced/sub-applications/)
- [FastAPI — CLI / fastapi dev](https://fastapi.tiangolo.com/fastapi-cli/)
- [Python — next() built-in](https://docs.python.org/3/library/functions.html#next)
- [Python — Function definitions](https://docs.python.org/3/reference/compound_stmts.html#function-definitions)
- [Python — Decorators](https://docs.python.org/3/glossary.html#term-decorator)
