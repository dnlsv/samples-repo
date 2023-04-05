<template>
  <TodoList :todos="todos" @delete-todo="deleteTodo" />
</template>

<script>
import TodoList from "./components/TodoList.vue";

export default {
  name: "App",
  data() {
    return {
      todos: ["Выполнить задание", "Сходить на пару", "Покушать"],
    };
  },
  methods: {
    deleteTodo(index) {
      this.todos.splice(index, 1);
    },
  },
  components: {
    TodoList,
  },
};
</script>

<style></style>
