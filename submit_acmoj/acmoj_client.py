#!/usr/bin/env python3
# -*- coding: utf-8 -*-

    def submit_code(self, problem_id: int, language: str, code_text: str) -> Optional[Dict]:
        data = {"language": language, "code": code_text}
        result = self._make_request("POST", f"/problem/{problem_id}/submit", data=data)
        if result and 'id' in result:
            self._save_submission_id(result['id'])
        return result
