import { defineConfig } from "eslint/config";
import pluginComplexity from "eslint-plugin-complexity";

export default defineConfig({
    files: ["**/*.{js,mjs,cjs,jsx,vue,ts,mts,cts,tsx}"],
    plugins: {
        complexity: pluginComplexity
    },
    rules: {
        "complexity": ["warn", { "max": 15 }],      // 圈复杂度 ≤ 15
        /*"max-depth": ["warn", 4],                   // 嵌套深度 ≤ 4
        "max-params": ["warn", 5],                  // 参数个数 ≤ 5
        "max-nested-callbacks": ["warn", 3],        // 回调嵌套 ≤ 3
        "max-lines-per-function": ["warn", 50],     // 函数行数 ≤ 50
        "max-lines": ["warn", 300]                  // 文件行数 ≤ 300*/
    }
});